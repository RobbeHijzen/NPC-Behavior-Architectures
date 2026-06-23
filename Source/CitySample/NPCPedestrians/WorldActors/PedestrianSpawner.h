#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "ZoneGraphSubsystem.h"

#include "PedestrianSpawner.generated.h"

UCLASS()
class CITYSAMPLE_API APedestrianSpawner : public AActor
{
	GENERATED_BODY()
	
public:

	APedestrianSpawner() {}
	virtual void PostInitializeComponents() override;

	FString GetSpawnClassName() const { return _PawnSpawningClass->GetName(); }
	int GetSpawnAmount() const { return _SpawnCount; }

protected:

	UPROPERTY(BlueprintReadWrite)
	int _SpawnCount{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _SpawnRange{ 3000.f };

	UPROPERTY(EditDefaultsOnly)
	FZoneGraphTagMask _ZoneGraphTagMaskAll{};
	UPROPERTY(EditDefaultsOnly)
	FZoneGraphTagMask _ZoneGraphTagMaskAny{};
	UPROPERTY(EditDefaultsOnly)
	FZoneGraphTagMask _ZoneGraphTagMaskNot{};

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<APawn> _PawnSpawningClass{};


	UFUNCTION(BlueprintCallable)
	void DoSpawning();

private:

	UZoneGraphSubsystem* _ZoneGraph{};

	bool GetRandomNavigableLocationAroundLocation(FVector location, float boxSize, FVector& outLocation);


};
