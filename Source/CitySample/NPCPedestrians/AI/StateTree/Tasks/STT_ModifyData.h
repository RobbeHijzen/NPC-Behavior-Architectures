#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STT_ModifyData.generated.h"

USTRUCT()
struct FModifyDataTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameter)
    FString DataName{};

    UPROPERTY(EditAnywhere, Category = Parameter)
    float ValuePerSecond{};

    UPROPERTY(EditAnywhere, Category = Output)
    float OutputValue{};

    TObjectPtr<APedestrian> Pedestrian{};
};

USTRUCT(category = "Data", meta = (DisplayName = "ModifyData", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_ModifyData : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FModifyDataTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FModifyDataTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;


private:
};

