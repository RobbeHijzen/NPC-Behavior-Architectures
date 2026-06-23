#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API FSMT_HasPendingConversation : public FSMTransition
{
public:

	FSMT_HasPendingConversation(const UFSMState* toState, UWorld* world, APedestrian* pedestrianPawn)
		: FSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};

};
