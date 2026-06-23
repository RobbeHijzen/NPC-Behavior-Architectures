#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "STC_HasFriendNearby.generated.h"

USTRUCT()
struct FTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;
};

USTRUCT(category = "Friends", meta = (DisplayName = "HasFriendNearby", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTC_HasFriendNearby : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

public:

    using FInstanceDataType = FTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FTaskInstanceData::StaticStruct(); }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

};