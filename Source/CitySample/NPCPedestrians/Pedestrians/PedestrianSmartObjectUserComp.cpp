#include "PedestrianSmartObjectUserComp.h"

UPedestrianSmartObjectUserComp::UPedestrianSmartObjectUserComp()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPedestrianSmartObjectUserComp::BeginPlay()
{
    Super::BeginPlay();

    _SmartObjectSubsystem = GetWorld()->GetSubsystem<USmartObjectSubsystem>();
    _ZoneGraphSubsystem = GetWorld()->GetSubsystem<UZoneGraphSubsystem>();
}

void UPedestrianSmartObjectUserComp::EndPlay(const EEndPlayReason::Type endPlayReason)
{
    Release();

    Super::EndPlay(endPlayReason);
}

bool UPedestrianSmartObjectUserComp::GetResultsOnSameLane(TArray<FSmartObjectRequestResult>& requestResults, FVector locationToCheck)
{
    if (!_ZoneGraphSubsystem) return false;

    TArray<FSmartObjectRequestResult> returnArray{};


    FZoneGraphLaneLocation laneLocation{};
    float distSq{};
    FZoneGraphTagFilter tagFilter{};
    FBox queryBox{ locationToCheck - 3000.f, locationToCheck + 3000.f };
    _ZoneGraphSubsystem->FindNearestLane(queryBox, tagFilter, laneLocation, distSq);

    for (auto& result : requestResults)
    {
        FVector slotLocation{ _SmartObjectSubsystem->GetSlotLocation(result.SlotHandle).GetValue() };

        queryBox = { slotLocation - 3000.f, slotLocation + 3000.f };
        FZoneGraphLaneLocation slotLaneLocation{};
        _ZoneGraphSubsystem->FindNearestLane(queryBox, tagFilter, slotLaneLocation, distSq);

        if (laneLocation.LaneHandle == slotLaneLocation.LaneHandle)
        {
            returnArray.Add(result);
        }
    }
    requestResults = returnArray;

    return !requestResults.IsEmpty();
}

bool UPedestrianSmartObjectUserComp::FindAndClaim(const FGameplayTag& activityTag, float searchRadius, FVector& outSlotLocation, FRotator& outSlotRotation)
{
    if (!_SmartObjectSubsystem || _ClaimHandle.IsValid())
    {
        return false;
    }

    const FVector location = GetOwner()->GetActorLocation();

    FSmartObjectRequest request{};
    request.QueryBox = FBox(location - FVector(searchRadius), location + FVector(searchRadius));
    request.Filter.ActivityRequirements = FGameplayTagQuery::MakeQuery_MatchTag(activityTag);

    TArray<FSmartObjectRequestResult> results;
    if (!_SmartObjectSubsystem->FindSmartObjects(request, results))
    {
        return false;
    }
    if (!GetResultsOnSameLane(results, location)) return false;

    // Try closest first
    float bestDistSqr = MAX_FLT;
    FSmartObjectRequestResult* bestResult = nullptr;

    for (FSmartObjectRequestResult& result : results)
    {
        if (TOptional<FVector> slotLoc = _SmartObjectSubsystem->GetSlotLocation(result.SlotHandle))
        {
            const float distSqr = FVector::DistSquared(location, slotLoc.GetValue());
            if (distSqr < bestDistSqr)
            {
                bestDistSqr = distSqr;
                bestResult = &result;
            }
        }
    }

    if (!bestResult)
    {
        return false;
    }
    _ClaimHandle = _SmartObjectSubsystem->MarkSlotAsClaimed(bestResult->SlotHandle, ESmartObjectClaimPriority::Normal);

    if (_ClaimHandle.IsValid())
    {
        FTransform slotTransform{};
        slotTransform = _SmartObjectSubsystem->GetSlotTransform(bestResult->SlotHandle).GetValue();
        outSlotLocation = slotTransform.GetLocation();
        outSlotRotation = slotTransform.GetRotation().Rotator();
        return true;
    }

    return false;
}

bool UPedestrianSmartObjectUserComp::HasNeabySmartObject(const FGameplayTag& activityTag, float searchRadius)
{
    if (!_SmartObjectSubsystem || _ClaimHandle.IsValid())
    {
        return false;
    }

    const FVector location = GetOwner()->GetActorLocation();


    FSmartObjectRequest request{};
    request.QueryBox = FBox(location - FVector(searchRadius), location + FVector(searchRadius));
    request.Filter.ActivityRequirements = FGameplayTagQuery::MakeQuery_MatchTag(activityTag);

    TArray<FSmartObjectRequestResult> results;
    _SmartObjectSubsystem->FindSmartObjects(request, results);


    return GetResultsOnSameLane(results, location);
}

void UPedestrianSmartObjectUserComp::Release()
{
    if (_ClaimHandle.IsValid() && _SmartObjectSubsystem)
    {
        _SmartObjectSubsystem->Release(_ClaimHandle);
        _ClaimHandle.Invalidate();
    }
}