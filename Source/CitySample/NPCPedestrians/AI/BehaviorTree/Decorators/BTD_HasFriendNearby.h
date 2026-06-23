#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HasFriendNearby.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_HasFriendNearby : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
