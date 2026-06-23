#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_IsAtRedLight.generated.h"

USTRUCT(category = "Movement", meta = (DisplayName = "IsAtRedLightInstanceData", ToolTip = "", Keywords = ""))
struct FIsAtRedLightTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor{};

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController{};

    UPROPERTY(EditAnywhere, Category = Parameter)
    bool Inverse{ false };

};

USTRUCT(category = "Movement", meta = (DisplayName = "IsAtRedLight", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_IsAtRedLight : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
	
public:

    using FInstanceDataType = FIsAtRedLightTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FIsAtRedLightTaskInstanceData::StaticStruct(); }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
