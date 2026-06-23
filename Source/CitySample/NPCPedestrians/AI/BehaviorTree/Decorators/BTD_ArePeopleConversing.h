#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_ArePeopleConversing.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_ArePeopleConversing : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
