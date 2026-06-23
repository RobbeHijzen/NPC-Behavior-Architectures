#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "STT_FollowClosestFriend.generated.h"

USTRUCT()
struct FFollowFriendTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    APedestrian* ClosestFriend{};
    UPedestrianMovementComponent* MoveComp{};
};

USTRUCT(category = "Movement", meta = (DisplayName = "FollowClosestFriend", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_FollowClosestFriend : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FFollowFriendTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FFollowFriendTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

};
