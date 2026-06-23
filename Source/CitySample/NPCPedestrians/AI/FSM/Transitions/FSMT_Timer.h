#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API FSMT_Timer : public FSMTransition
{
public:
	FSMT_Timer(const UFSMState* toState, UWorld* world, float delay)
		: FSMTransition(toState, world)
		, _Delay{delay}
	{ }

	bool Evaluate(float deltaTime) const override;

private:

	float _Delay{};
	mutable float _CurrentTime{};
};
