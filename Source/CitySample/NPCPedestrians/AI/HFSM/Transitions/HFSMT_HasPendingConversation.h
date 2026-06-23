#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API HFSMT_HasPendingConversation : public HFSMTransition
{
public:

	HFSMT_HasPendingConversation(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};

};
