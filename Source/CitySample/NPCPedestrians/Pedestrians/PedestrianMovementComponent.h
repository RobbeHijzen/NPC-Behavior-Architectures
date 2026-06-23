#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZoneGraphSubsystem.h"
#include "NPCSpatialGrid.h"
#include "Pedestrian.h"

#include "PedestrianMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRejoinedLane);

UENUM(BlueprintType)
enum class MovementState : uint8
{
	Idle = 0 UMETA(DisplayName = "Idle"),
	Wander = 150 UMETA(DisplayName = "Wander"),
	Run = 250 UMETA(DisplayName = "Run")
};

UENUM(BlueprintType)
enum class EFollowerState : uint8
{
	FollowingLane,
	LeavingLane,
	OffLane,
	ReturningToLane
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSAMPLE_API UPedestrianMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPedestrianMovementComponent();

	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMovementState(MovementState newMovementState) { _CurrentMovementState = newMovementState; };

	UFUNCTION(BlueprintCallable)
	bool LeaveLaneForSmartObject(const FGameplayTag& smartObjectType);

	UFUNCTION(BlueprintCallable)
	bool LeaveLaneForLocation(const FVector& location);

	UFUNCTION(BlueprintCallable)
	void ReturnToLane();

	UFUNCTION(BlueprintCallable)
	EFollowerState GetFollowerState() const { return _FollowerState; }

	UFUNCTION(BlueprintCallable)
	bool IsCurrentLaneWalkable() const;

	UFUNCTION(BlueprintCallable)
	void SetOffLaneAnimationType(EAnimationType animationType) { _OffLaneAnimation = animationType; }

	UPROPERTY(BlueprintAssignable)
	FOnRejoinedLane _OnRejoinedLane;


	UFUNCTION(BlueprintCallable)
	void SetEvadeLocation(bool newEvade) { _EvadeLocation = newEvade; }

	UFUNCTION(BlueprintCallable)
	void SetLocationToEvade(FVector location) { _LocationToEvade = location; }

protected:

	// Movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _RandomMovementSpeedMultiplierMin{ 0.85f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _RandomMovementSpeedMultiplierMax{ 1.15f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxMovementSpeedMultiplier{ 1.3f };


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _RandomLaneOffsetMax{ 75.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _LookAheadDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _SmartObjectSearchRadius = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _RotationSpeed = 270.f;

	// Avoidance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _AvoidanceRadius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _AvoidanceStrength = 150.f;

	// ZoneGraph
	UPROPERTY(BlueprintReadOnly)
	EFollowerState _FollowerState = EFollowerState::FollowingLane;

	UPROPERTY()
	FZoneGraphLaneLocation _StoredLaneLocation{}; // Where we left the lane

	UPROPERTY()
	FVector _OffLaneDestination{};

	UPROPERTY()
	FRotator _OffLaneRotation{};

private:

	// Movement
	MovementState _CurrentMovementState{ MovementState::Idle };
	EAnimationType _OffLaneAnimation{ EAnimationType::Idle };

	float _RandomMovementSpeedMultiplier{};
	float _RandomLaneOffset{};

	FVector _TargetLocation{};
	FVector _AvoidanceForce{};
	FVector _DesiredVelocity{};

	bool _EvadeLocation{};
	FVector _LocationToEvade{};

	// Zonegraph

	UZoneGraphSubsystem* _ZoneGraph{};
	UNPCSpatialGrid* _SpatialGrid{};
	FZoneGraphLaneLocation _CurrentLaneLocation{};

	void UpdateLaneTargetLocation();
	void CalculateAvoidanceSpatially();

	void InitializeZoneGraph();
	FZoneGraphLaneLocation GetRandomNextLane();
	void SetCurrentLane(FZoneGraphLaneLocation newLaneLocation);
	void RotateTowardTarget(float deltaTime, FRotator targetRotator);
};
