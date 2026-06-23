#include "PedestrianMovementComponent.h"
#include "PedestrianSmartObjectUserComp.h"
#include "ZoneGraphSettings.h"

UPedestrianMovementComponent::UPedestrianMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

}

void UPedestrianMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_ZoneGraph = GetWorld()->GetSubsystem<UZoneGraphSubsystem>();
	InitializeZoneGraph();

	_SpatialGrid = GetWorld()->GetSubsystem<UNPCSpatialGrid>();
	if (_SpatialGrid)
		_SpatialGrid->Register(GetOwner());

	_RandomMovementSpeedMultiplier = FMath::FRandRange(_RandomMovementSpeedMultiplierMin, _RandomMovementSpeedMultiplierMax);
	_RandomLaneOffset = FMath::FRandRange(0, _RandomLaneOffsetMax);
}

void UPedestrianMovementComponent::InitializeZoneGraph()
{
	if (!_ZoneGraph) return;

	FZoneGraphLaneLocation laneLocation{};
	float distSq{};
	FZoneGraphTagFilter tagFilter{};

	FVector actorLocation{ GetOwner()->GetActorLocation() };
	FBox queryBox{ actorLocation - 400.f, actorLocation + 400.f };

	if (_ZoneGraph->FindNearestLane(queryBox, tagFilter, laneLocation, distSq))
	{
		SetCurrentLane(laneLocation);
	}

}


void UPedestrianMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!_ZoneGraph) return;

	// If idling -> return
	if (_CurrentMovementState == MovementState::Idle)
	{
		_TargetLocation = GetOwner()->GetActorLocation();
		_DesiredVelocity = FVector::ZeroVector;
		_AvoidanceForce = FVector::ZeroVector;

		return;
	}

	// Variables needed for movement
	const FVector currentLocation = GetOwner()->GetActorLocation();
	int baseMovementSpeed{ int(_CurrentMovementState) };
	float movementSpeed = baseMovementSpeed * _RandomMovementSpeedMultiplier;
	const float maxSpeed = baseMovementSpeed * _MaxMovementSpeedMultiplier;



	switch (_FollowerState)
	{
	case EFollowerState::FollowingLane:
	{

		UpdateLaneTargetLocation();
		CalculateAvoidanceSpatially();

		const FVector toTarget = _TargetLocation - currentLocation;
		const FVector desiredDirection = toTarget.GetSafeNormal2D();

		FVector evadeForce{};
		if (_EvadeLocation)
		{
			
			const float dist = FVector::Dist(currentLocation, _LocationToEvade);
			const float strength = 1.0f - (dist / _AvoidanceRadius);
			evadeForce = (currentLocation - _LocationToEvade).GetSafeNormal2D() * strength;
		}

		_DesiredVelocity = desiredDirection * movementSpeed + _AvoidanceForce + evadeForce;

		float distSq{};
		_ZoneGraph->FindNearestLocationOnLane(_CurrentLaneLocation.LaneHandle, currentLocation, 300.f, _CurrentLaneLocation, distSq);

		break;

	}
	case EFollowerState::LeavingLane:
	{
		const FVector toTarget = _OffLaneDestination - currentLocation;
		const float distToDestination = toTarget.Size2D();

		if (distToDestination < 75.f)
		{
			if (auto pedestrian = Cast<APedestrian>(GetOwner()))
			{
				pedestrian->SetAnimation(_OffLaneAnimation, true);

				if(_OffLaneRotation != FRotator{})
					pedestrian->SetActorRotation(_OffLaneRotation);

				_OffLaneRotation = FRotator{};
			}
			_FollowerState = EFollowerState::OffLane;
			_DesiredVelocity = FVector::ZeroVector;

		}
		else
		{
			// Move toward destination, still avoid others
			CalculateAvoidanceSpatially();

			_DesiredVelocity = toTarget.GetSafeNormal2D() * movementSpeed + _AvoidanceForce;
		}
		break;
	}
	case EFollowerState::OffLane:
	{
		// Stationary, waiting
		_DesiredVelocity = FVector::ZeroVector;
		break;
	}
	case EFollowerState::ReturningToLane:
	{
		const FVector lanePosition = _StoredLaneLocation.Position;
		const FVector toLane = lanePosition - currentLocation;
		const float distToLane = toLane.Size2D();

		if (distToLane < 50.f)
		{
			// Back on the lane, resume following
			_CurrentLaneLocation = _StoredLaneLocation;
			_FollowerState = EFollowerState::FollowingLane;

			_OnRejoinedLane.Broadcast();
		}
		else
		{
			CalculateAvoidanceSpatially();
			_DesiredVelocity = toLane.GetSafeNormal2D() * movementSpeed + _AvoidanceForce;
		}
		break;
	}
	}


	// Clamp to max speed
	if (_DesiredVelocity.SizeSquared2D() > maxSpeed * maxSpeed)
	{
		_DesiredVelocity = _DesiredVelocity.GetSafeNormal2D() * maxSpeed;
	}

	FVector deltaPos{ _DesiredVelocity * DeltaTime };
	GetOwner()->AddActorWorldOffset(deltaPos);

	if (_DesiredVelocity.SizeSquared() >= 1.f)
		RotateTowardTarget(DeltaTime, _DesiredVelocity.ToOrientationRotator());
}

bool UPedestrianMovementComponent::LeaveLaneForSmartObject(const FGameplayTag& smartObjectType)
{
	if (_FollowerState != EFollowerState::FollowingLane)
	{
		return false;
	}

	UPedestrianSmartObjectUserComp* smartObjectUserComp{ GetOwner()->GetComponentByClass<UPedestrianSmartObjectUserComp>() };
	if (!smartObjectUserComp) return false;

	FVector smartObjectLocation{};
	FRotator smartObjectRocation{};

	bool foundSmartObject = smartObjectUserComp->FindAndClaim(smartObjectType, _SmartObjectSearchRadius, smartObjectLocation, smartObjectRocation);
	if (!foundSmartObject) return false;


	// Store where we left the lane so we can return
	_StoredLaneLocation = _CurrentLaneLocation;
	_OffLaneDestination = smartObjectLocation;
	_OffLaneRotation = smartObjectRocation;
	_FollowerState = EFollowerState::LeavingLane;


	return true;
}

bool UPedestrianMovementComponent::LeaveLaneForLocation(const FVector& location)
{
	if (_FollowerState != EFollowerState::FollowingLane && _FollowerState != EFollowerState::LeavingLane)
	{
		return false;
	}

	_StoredLaneLocation = _CurrentLaneLocation;
	_OffLaneDestination = location;
	_FollowerState = EFollowerState::LeavingLane;

	return true;
}

void UPedestrianMovementComponent::ReturnToLane()
{
	if (_FollowerState == EFollowerState::OffLane)
	{
		_FollowerState = EFollowerState::ReturningToLane;
	}
}

bool UPedestrianMovementComponent::IsCurrentLaneWalkable() const
{
	FZoneGraphTagMask tags{};
	_ZoneGraph->GetLaneTags(_CurrentLaneLocation.LaneHandle, tags);

	FZoneGraphTag notAllowedTag = _ZoneGraph->GetTagByName(FName{"RedLight"});
	return !tags.Contains(notAllowedTag);
}

void UPedestrianMovementComponent::UpdateLaneTargetLocation()
{
	FZoneGraphLaneLocation lookAheadLocation{};

	if (_ZoneGraph->AdvanceLaneLocation(_CurrentLaneLocation, _LookAheadDistance, lookAheadLocation))
	{
		// Check if the pedestrian is near the end of the lane

		float laneLength{};
		_ZoneGraph->GetLaneLength(_CurrentLaneLocation.LaneHandle, laneLength);

		if (lookAheadLocation.DistanceAlongLane >= laneLength)
		{
			SetCurrentLane(GetRandomNextLane());
			_ZoneGraph->AdvanceLaneLocation(_CurrentLaneLocation, _LookAheadDistance, lookAheadLocation);
		}


		_TargetLocation = lookAheadLocation.Position;

		// Apply lateral offset
		const FVector LaneRight = FVector::CrossProduct(lookAheadLocation.Up, lookAheadLocation.Direction);
		_TargetLocation += LaneRight * _RandomLaneOffset * -1; // * -1 so the offset is only into the left side (so the NPC doesnt go out of bounds, since the left side is where the lane from the other direction comes from)

	}

}

void UPedestrianMovementComponent::CalculateAvoidanceSpatially()
{
	if (!_SpatialGrid) return;

	const FVector myLocation = GetOwner()->GetActorLocation();
	FVector separationForce = FVector::ZeroVector;

	TArray<AActor*> nearbyActors{};
	_SpatialGrid->QueryRadius(myLocation, _AvoidanceRadius, nearbyActors);

	for (auto other : nearbyActors)
	{
		if (other == GetOwner())
		{
			continue;
		}

		// Only avoid other ZoneGraph followers
		if (!other->FindComponentByClass<UPedestrianMovementComponent>())
		{
			continue;
		}

		float awayStrengthMultiplier{ 1.f };
		const FVector otherLocation = other->GetActorLocation();
		const FVector away = myLocation - otherLocation;
		const FVector forward = GetOwner()->GetActorForwardVector().GetSafeNormal();

		double dot{ GetOwner()->GetActorForwardVector().Dot(away.GetSafeNormal()) };
		if (dot > 0.f)
		{
			awayStrengthMultiplier = 1.f - dot;
		}


		const float distSqr = away.SizeSquared2D();
		const float radiusSqr = _AvoidanceRadius * _AvoidanceRadius;

		if (distSqr < radiusSqr && distSqr > KINDA_SMALL_NUMBER)
		{
			const float dist = FMath::Sqrt(distSqr);
			const float strength = 1.0f - (dist / _AvoidanceRadius);
			separationForce += away.GetSafeNormal2D() * strength * _AvoidanceStrength * awayStrengthMultiplier;
		}
	}

	_AvoidanceForce = separationForce;
}


FZoneGraphLaneLocation UPedestrianMovementComponent::GetRandomNextLane()
{
	TArray<FZoneGraphLinkedLane> linkedLanes{};
	_ZoneGraph->GetLinkedLanes(_CurrentLaneLocation.LaneHandle, EZoneLaneLinkType::Outgoing, EZoneLaneLinkFlags::All, EZoneLaneLinkFlags::None, linkedLanes);
	if (linkedLanes.IsEmpty()) return {};

	auto& linkedLane{ linkedLanes[FMath::RandRange(0, linkedLanes.Num() - 1)] };


	FZoneGraphLaneLocation laneLocation{};
	float distSq{};

	FVector actorLocation{ GetOwner()->GetActorLocation() };
	FBox queryBox{ actorLocation - 400.f, actorLocation + 400.f };

	_ZoneGraph->FindNearestLocationOnLane(linkedLane.DestLane, queryBox, laneLocation, distSq);
	return laneLocation;
}

void UPedestrianMovementComponent::SetCurrentLane(FZoneGraphLaneLocation newLaneLocation)
{
	_CurrentLaneLocation = newLaneLocation;
	_TargetLocation = newLaneLocation.Position;
}

void UPedestrianMovementComponent::RotateTowardTarget(float deltaTime, FRotator targetRotator)
{
	FQuat targetDirection{ targetRotator.Quaternion() };
	FQuat currentDirection{ GetOwner()->GetActorRotation().Quaternion() };
	float maxRotationThisFrame = _RotationSpeed * deltaTime;

	FQuat deltaQuat = targetDirection * currentDirection.Inverse();
	float deltaAngle = FMath::RadiansToDegrees(deltaQuat.GetAngle());

	if (deltaAngle <= maxRotationThisFrame)
	{
		currentDirection = targetDirection;
	}
	else
	{
		float alpha = maxRotationThisFrame / deltaAngle;
		currentDirection = FQuat::Slerp(currentDirection, targetDirection, alpha);
	}


	if (AActor* owner = GetOwner())
	{
		owner->SetActorRotation(currentDirection);
	}
}
