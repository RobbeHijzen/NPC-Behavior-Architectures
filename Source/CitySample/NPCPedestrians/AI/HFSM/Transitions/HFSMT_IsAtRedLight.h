#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"

class CITYSAMPLE_API HFSMT_IsAtRedLight : public HFSMTransition
{
public:

	HFSMT_IsAtRedLight(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, bool inverse = false)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _Inverse{ inverse }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	bool _Inverse{ false };

};
