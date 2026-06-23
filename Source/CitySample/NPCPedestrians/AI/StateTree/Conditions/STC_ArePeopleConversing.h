#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_ArePeopleConversing.generated.h"


USTRUCT()
struct FArePeopleConversingTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;
};

USTRUCT(category = "Friends", meta = (DisplayName = "ArePeopleConversing", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_ArePeopleConversing : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

public:

    using FInstanceDataType = FArePeopleConversingTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FArePeopleConversingTaskInstanceData::StaticStruct(); }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};