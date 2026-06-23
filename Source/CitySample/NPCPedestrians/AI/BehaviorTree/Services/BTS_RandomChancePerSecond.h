#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_RandomChancePerSecond.generated.h"


UCLASS()
class CITYSAMPLE_API UBTS_RandomChancePerSecond : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTS_RandomChancePerSecond();

	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	) override;

	UPROPERTY(EditAnywhere, Category = Input)
	float _ChancePerSecond{ 0.5f };
};
