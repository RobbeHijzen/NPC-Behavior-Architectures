#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_RandomChance.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_RandomChance : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = Input)
	float _Chance{ 0.5f };
};
