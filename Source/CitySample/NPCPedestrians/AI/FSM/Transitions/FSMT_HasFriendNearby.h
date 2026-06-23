#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API FSMT_HasFriendNearby : public FSMTransition
{
public:

	FSMT_HasFriendNearby(const UFSMState* toState, UWorld* world, APedestrian* pedestrian)
		: FSMTransition(toState, world)
		, _Pedestrian{ pedestrian }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	float _RandomChancePerSecond{ 0.02f };

};
