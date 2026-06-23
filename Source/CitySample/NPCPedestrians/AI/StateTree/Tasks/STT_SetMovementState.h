#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "STT_SetMovementState.generated.h"


USTRUCT()
struct FSetMovementStateTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameters)
    MovementState NewMovementState{ MovementState::Idle };
};

USTRUCT(category = "Movement", meta = (DisplayName = "SetMovementState", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_SetMovementState : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSetMovementStateTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FSetMovementStateTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

private:
};

