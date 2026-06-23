#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_HasNearbySmartObject.generated.h"

USTRUCT(category = "SmartObjects", meta = (DisplayName = "HasNearbySmartObjectInstanceData", ToolTip = "", Keywords = ""))
struct FSmartObjectInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Parameter)
    FGameplayTag SmartObjectTag{};

    UPROPERTY(EditAnywhere, Category = Parameter)
    float Radius{ 3000.f };
};


USTRUCT(category = "SmartObjects", meta = (DisplayName = "HasNearbySmartObject", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_HasNearbySmartObject : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

public:

    using FInstanceDataType = FSmartObjectInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FSmartObjectInstanceData::StaticStruct(); }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};