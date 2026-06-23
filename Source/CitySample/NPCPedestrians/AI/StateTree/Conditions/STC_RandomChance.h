#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "STC_RandomChance.generated.h"

USTRUCT(category = "Random", meta = (DisplayName = "RandomChanceInstanceData", ToolTip = "", Keywords = ""))
struct FRandomChanceInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Parameter)
    float ChancePerSecond{ 0.02f };
};


USTRUCT(category = "Random", meta = (DisplayName = "RandomChance", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_RandomChance : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
	
    public:

        using FInstanceDataType = FRandomChanceInstanceData;
        virtual const UStruct* GetInstanceDataType() const override { return FRandomChanceInstanceData::StaticStruct(); }

        virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};
