#include "NPCSpatialGrid.h"
#include "Pedestrian.h"

void UNPCSpatialGrid::Register(AActor* Actor)
{
    if (!Actor || ActorToCellMap.Contains(Actor))
    {
        return;
    }

    const FIntVector Cell = LocationToCell(Actor->GetActorLocation());
    AddToCell(Actor, Cell);
    ActorToCellMap.Add(Actor, Cell);
}

void UNPCSpatialGrid::Unregister(AActor* Actor)
{
    if (!Actor)
    {
        return;
    }

    if (const FIntVector* Cell = ActorToCellMap.Find(Actor))
    {
        RemoveFromCell(Actor, *Cell);
        ActorToCellMap.Remove(Actor);
    }
}

void UNPCSpatialGrid::AddToCell(AActor* Actor, const FIntVector& Cell)
{
    Grid.FindOrAdd(Cell).Add(Actor);
}

void UNPCSpatialGrid::RemoveFromCell(AActor* Actor, const FIntVector& Cell)
{
    if (TArray<AActor*>* CellActors = Grid.Find(Cell))
    {
        CellActors->RemoveSwap(Actor);
        if (CellActors->IsEmpty())
        {
            Grid.Remove(Cell);
        }
    }
}

void UNPCSpatialGrid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update cells for all moved actors
    for (auto It = ActorToCellMap.CreateIterator(); It; ++It)
    {
        AActor* Actor = It->Key;

        if (!IsValid(Actor))
        {
            RemoveFromCell(Actor, It->Value);
            It.RemoveCurrent();
            continue;
        }

        const FIntVector NewCell = LocationToCell(Actor->GetActorLocation());

        if (NewCell != It->Value)
        {
            RemoveFromCell(Actor, It->Value);
            AddToCell(Actor, NewCell);
            It->Value = NewCell;
        }
    }
}

void UNPCSpatialGrid::QueryRadius(const FVector& Center, float Radius, TArray<AActor*>& OutActors) const
{
    OutActors.Reset();

    const FIntVector CenterCell = LocationToCell(Center);
    const int32 CellSpan = FMath::CeilToInt(Radius / CellSize);
    const float RadiusSqr = Radius * Radius;

    for (int32 X = -CellSpan; X <= CellSpan; ++X)
    {
        for (int32 Y = -CellSpan; Y <= CellSpan; ++Y)
        {
            const FIntVector Cell(CenterCell.X + X, CenterCell.Y + Y, 0);

            if (const TArray<AActor*>* CellActors = Grid.Find(Cell))
            {
                for (AActor* Actor : *CellActors)
                {
                    if (FVector::DistSquared2D(Center, Actor->GetActorLocation()) <= RadiusSqr)
                    {
                        OutActors.Add(Actor);
                    }
                }
            }
        }
    }
}
