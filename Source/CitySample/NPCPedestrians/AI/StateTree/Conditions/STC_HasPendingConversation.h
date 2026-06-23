#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_HasPendingConversation.generated.h"

USTRUCT(category = "Conversing", meta = (DisplayName = "ConverseInstanceData", ToolTip = "", Keywords = ""))
struct FConverseInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor{};

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController{};
};

USTRUCT(category = "Conversing", meta = (DisplayName = "HasPendingConversation", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_HasPendingConversation : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
public: 

    using FInstanceDataType = FConverseInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FConverseInstanceData::StaticStruct(); }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};