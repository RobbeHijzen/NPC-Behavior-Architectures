#pragma once

#include "CoreMinimal.h"
#include "../FSMTransition.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../FloatComparison.h"

class CITYSAMPLE_API FSMT_CheckData : public FSMTransition
{
public:
	
	FSMT_CheckData(const UFSMState* toState, UWorld* world, APedestrian* pedestrianPawn, FString dataNameToCheck, EFloatComparison operation, float rightValue)
		: FSMTransition(toState, world)
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
