#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../FloatComparison.h"


class CITYSAMPLE_API HFSMT_ShouldSit : public HFSMTransition
{
public:
	HFSMT_ShouldSit(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};

};
