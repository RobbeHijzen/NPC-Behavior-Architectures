#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "STT_LeaveLaneForSmartObject.generated.h"

USTRUCT()
struct FLeaveLaneTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameter)
    FGameplayTag SmartObjectTag{};

    UPROPERTY(EditAnywhere, Category = Parameter)
    float MinDuration{ 20.f };

    UPROPERTY(EditAnywhere, Category = Parameter)
    float MaxDuration{ 30.f };

    UPROPERTY(EditAnywhere, Category = Parameter)
    EAnimationType AnimationTypeWhenAtLocation{};

    float RandomDuration{};
    float CurrentDuration{};

    UPedestrianMovementComponent* MoveComp{};
};

USTRUCT(category = "Data", meta = (DisplayName = "LeaveLaneForSmartObject", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_LeaveLaneForSmartObject : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FLeaveLaneTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FLeaveLaneTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
    void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;


private:
};

