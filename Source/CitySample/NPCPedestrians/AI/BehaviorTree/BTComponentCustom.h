#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BTComponentCustom.generated.h"


UCLASS()
class CITYSAMPLE_API UBTComponentCustom : public UBehaviorTreeComponent
{
	GENERATED_BODY()

public:

	UBTComponentCustom() { PrimaryComponentTick.bCanEverTick = true; }
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float _TickInterval{ 0.25f };
	float _CurrentTickTime{};
};
