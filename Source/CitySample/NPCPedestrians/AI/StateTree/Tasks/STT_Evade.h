#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STT_Evade.generated.h"


USTRUCT()
struct FEvadeTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

};

USTRUCT(category = "Movement", meta = (DisplayName = "Evade", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_Evade : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FEvadeTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FEvadeTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};
