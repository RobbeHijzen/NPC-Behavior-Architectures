#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HasSmartObjectNearby.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_HasSmartObjectNearby : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = Input)
	FGameplayTag _SmartObjectTag{};

	UPROPERTY(EditAnywhere, Category = Input)
	float _Range{ 3000.f };
};
