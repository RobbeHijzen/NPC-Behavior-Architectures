#include "PedestrianSpawner.h"
#include "../Pedestrians/Pedestrian.h"

void APedestrianSpawner::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    UWorld* world = GetWorld();
    if (world) _ZoneGraph = world->GetSubsystem<UZoneGraphSubsystem>();
}

bool APedestrianSpawner::GetRandomNavigableLocationAroundLocation(FVector location, float boxSize, FVector& outLocation)
{
    if (!_ZoneGraph)
        return false;

    FBox queryBox{ location - boxSize, location + boxSize };
    FZoneGraphTagFilter tagFilter{};
    tagFilter.AllTags = _ZoneGraphTagMaskAll;
    tagFilter.AnyTags = _ZoneGraphTagMaskAny;
    tagFilter.NotTags = _ZoneGraphTagMaskNot;

    // 1. Find all lanes within the query bounds
    TArray<FZoneGraphLaneHandle> overlappingLanes;
    if (!_ZoneGraph->FindOverlappingLanes(queryBox, tagFilter, overlappingLanes) || overlappingLanes.Num() == 0)
    {
        return false;
    }

    // 2. Calculate cumulative weights (lane lengths)
    TArray<float> cumulativeWeights;
    cumulativeWeights.Reserve(overlappingLanes.Num());
    float totalWeight = 0.f;

    for (const FZoneGraphLaneHandle& handle : overlappingLanes)
    {
        float laneLength{};
        _ZoneGraph->GetLaneLength(handle, laneLength);

        totalWeight += laneLength;
        cumulativeWeights.Add(totalWeight);
    }

    if (totalWeight <= 0.f)
    {
        return false;
    }

    // 3. Pick random value in total weight range
    const float randomValue = FMath::FRandRange(0.f, totalWeight);

    // 4. Find which lane this falls into using binary search
    int32 selectedIndex = Algo::LowerBound(cumulativeWeights, randomValue);
    selectedIndex = FMath::Clamp(selectedIndex, 0, overlappingLanes.Num() - 1);

    const FZoneGraphLaneHandle& laneHandle = overlappingLanes[selectedIndex];

    // 5. Pick a random distance along the lane
    float laneLength{};
    _ZoneGraph->GetLaneLength(laneHandle, laneLength);

    const float randomDistance = FMath::FRandRange(0.f, laneLength);

    // 6. Calculate the location at that distance
    FZoneGraphLaneLocation laneLocation;
    if (_ZoneGraph->CalculateLocationAlongLane(laneHandle, randomDistance, laneLocation))
    {
        outLocation = laneLocation.Position;
        return true;
    }

    return false;
}

void APedestrianSpawner::DoSpawning()
{
    UWorld* world = GetWorld();
    if (world)
    {
        for (int index{}; index < _SpawnCount; ++index)
        {
            FVector loc{};
            GetRandomNavigableLocationAroundLocation(GetActorLocation(), _SpawnRange, loc);
            FTransform spawnTransform{};
            spawnTransform.SetLocation(loc);
            spawnTransform.SetRotation(FQuat{ {0,0,1}, FMath::RandRange(-PI, PI) });


            FActorSpawnParameters spawnParams{};
            spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            world->SpawnActor<APawn>(_PawnSpawningClass, spawnTransform, spawnParams);
        }



    }
}

