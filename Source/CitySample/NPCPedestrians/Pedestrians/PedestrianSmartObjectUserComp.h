#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SmartObjectTypes.h"
#include "SmartObjectRequestTypes.h"
#include "SmartObjectSubsystem.h"
#include "ZoneGraphSubsystem.h"

#include "PedestrianSmartObjectUserComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSAMPLE_API UPedestrianSmartObjectUserComp : public UActorComponent
{
	GENERATED_BODY()

public:

    UPedestrianSmartObjectUserComp();

    UFUNCTION(BlueprintCallable, Category = "Smart Object")
    bool FindAndClaim(const FGameplayTag& activityTag, float searchRadius, FVector& outSlotLocation, FRotator& outSlotRotation);

    UFUNCTION(BlueprintCallable, Category = "Smart Object")
    bool HasNeabySmartObject(const FGameplayTag& activityTag, float searchRadius);

    UFUNCTION(BlueprintCallable, Category = "Smart Object")
    void Release();

    UFUNCTION(BlueprintCallable, Category = "Smart Object")
    bool HasClaim() const { return _ClaimHandle.IsValid(); }

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
    UPROPERTY()
    TObjectPtr<USmartObjectSubsystem> _SmartObjectSubsystem{};
    TObjectPtr<UZoneGraphSubsystem> _ZoneGraphSubsystem{};

    FSmartObjectClaimHandle _ClaimHandle{};

    bool GetResultsOnSameLane(TArray<FSmartObjectRequestResult>& requestResults, FVector locationToCheck);
};
