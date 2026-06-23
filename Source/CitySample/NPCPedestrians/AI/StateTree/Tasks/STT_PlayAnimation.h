#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STT_PlayAnimation.generated.h"

USTRUCT()
struct FPlayAnimationTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameter)
    EAnimationType AnimationType{};

    UPROPERTY(EditAnywhere, Category = Parameter)
    bool LoopAnimation{ false };

    FTimerHandle AnimationTimerHandle{};
    bool HasFinishedAnimation{ false };
};

USTRUCT(category = "Animation", meta = (DisplayName = "PlayAnimation", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_PlayAnimation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FPlayAnimationTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FPlayAnimationTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;


private:
};


