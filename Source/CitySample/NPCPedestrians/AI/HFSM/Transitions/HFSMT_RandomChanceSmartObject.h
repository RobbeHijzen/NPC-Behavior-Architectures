#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"

class CITYSAMPLE_API HFSMT_RandomChanceSmartObject : public HFSMTransition
{
public:

	HFSMT_RandomChanceSmartObject(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, FGameplayTag tag)
		: HFSMTransition(toState, world)
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
