#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API HFSMT_ArePeopleConversing : public HFSMTransition
{
public:

	HFSMT_ArePeopleConversing(const UHFSMState* toState, UWorld* world, APedestrian* pedestrian)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrian }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	float _RandomChancePerSecond{ 0.02f };

};
