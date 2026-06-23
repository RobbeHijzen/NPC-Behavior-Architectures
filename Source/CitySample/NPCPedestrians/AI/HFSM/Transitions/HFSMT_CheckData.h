#pragma once

#include "CoreMinimal.h"
#include "../HFSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../FloatComparison.h"

class CITYSAMPLE_API HFSMT_CheckData : public HFSMTransition
{
public:

	HFSMT_CheckData(const UHFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, FString dataNameToCheck, EFloatComparison operation, float rightValue)
		: HFSMTransition(toState, world)
		, _Pedestrian{ pedestrianPawn }
		, _DataName{ dataNameToCheck }
		, _Operation{ operation }
		, _RightValue{ rightValue }
	{
	}

	bool Evaluate(float deltaTime) const override;

private:

	APedestrian* _Pedestrian{};
	FString _DataName{};
	EFloatComparison _Operation{};
	float _RightValue{};
};
