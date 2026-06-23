#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include <functional>

class CITYSAMPLE_API HFSMT_BoolFunction : public HFSMTransition
{
public:
	HFSMT_BoolFunction(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, std::function<bool()> func)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _Function{ func }
	{

	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	std::function<bool()> _Function;
};
