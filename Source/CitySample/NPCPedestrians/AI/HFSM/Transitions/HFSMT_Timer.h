#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API HFSMT_Timer : public HFSMTransition
{
public:
	HFSMT_Timer(const UHFSMState* toState, UWorld* world, float delay)
		: HFSMTransition(toState, world)
		, _Delay{ delay }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	float _Delay{};
	mutable float _CurrentTime{};
};
