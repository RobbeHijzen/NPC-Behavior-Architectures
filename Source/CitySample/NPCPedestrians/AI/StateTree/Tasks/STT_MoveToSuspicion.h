#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STT_MoveToSuspicion.generated.h"

USTRUCT()
struct FMoveToSuspicionTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;
};

USTRUCT(category = "Movement", meta = (DisplayName = "MoveToSuspicion", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_MoveToSuspicion : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

    using FInstanceDataType = FMoveToSuspicionTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FMoveToSuspicionTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};
