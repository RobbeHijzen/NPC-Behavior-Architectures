#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_RandomChance.generated.h"


UCLASS()
class CITYSAMPLE_API UBTD_RandomChance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_RandomChance()
	{
		bNotifyTick = true;
	}

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Input)
	float _ChancePerSecond{ 0.5f };

	UPROPERTY(EditAnywhere, Category = Input)
	bool _UseDeltaTime{ true };
};
