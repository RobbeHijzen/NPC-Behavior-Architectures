#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STT_Confront.generated.h"


USTRUCT()
struct FConfrontTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameter)
    float DistancePercentage{ 1.f };
};

USTRUCT(category = "Movement", meta = (DisplayName = "Confront", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_Confront : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FConfrontTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FConfrontTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};
