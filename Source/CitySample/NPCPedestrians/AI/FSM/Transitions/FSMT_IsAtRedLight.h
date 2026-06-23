#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API FSMT_IsAtRedLight : public FSMTransition
{
public:

	FSMT_IsAtRedLight(const UFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, bool inverse = false)
		: FSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _Inverse{ inverse }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	bool _Inverse{ false };
};
