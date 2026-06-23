#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NPCSpatialGrid.generated.h"

class APedestrian;

UCLASS()
class CITYSAMPLE_API UNPCSpatialGrid : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(UNPCSpatialGrid, STATGROUP_Tickables);
    }

    void Register(AActor* Actor);
    void Unregister(AActor* Actor);
    void QueryRadius(const FVector& Center, float Radius, TArray<AActor*>& OutActors) const;

    int32 GetNumRegistered() const { return ActorToCellMap.Num(); }

private:
    // Tuned for typical avoidance radius of 100-200 units
    static constexpr float CellSize = 150.f;

    FIntVector LocationToCell(const FVector& Location) const
    {
        return FIntVector(
            FMath::FloorToInt(Location.X / CellSize),
            FMath::FloorToInt(Location.Y / CellSize),
            0
        );
    }

    void RemoveFromCell(AActor* Actor, const FIntVector& Cell);
    void AddToCell(AActor* Actor, const FIntVector& Cell);

    TMap<FIntVector, TArray<AActor*>> Grid;
    TMap<AActor*, FIntVector> ActorToCellMap;
};
