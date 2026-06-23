#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"

class CITYSAMPLE_API FSMT_RandomChanceSmartObject : public FSMTransition
{
public:

	FSMT_RandomChanceSmartObject(const UFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, FGameplayTag tag)
		: FSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _SmartObjectTag{ tag }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	FGameplayTag _SmartObjectTag{};

	float _RandomChancePerSecond{ 0.02f };
	float _Radius{ 3000.f };
};
