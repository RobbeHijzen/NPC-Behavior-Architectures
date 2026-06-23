#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsAtRedLight.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_IsAtRedLight : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_IsAtRedLight()
	{
		bNotifyTick = true;
	}

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds) override;
};
