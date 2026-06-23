#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include <functional>

class CITYSAMPLE_API FSMT_BoolFunction : public FSMTransition
{
public:
	FSMT_BoolFunction(const UFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, std::function<bool()> func)
		: FSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _Function{ func }
	{

	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	std::function<bool()> _Function;
};
