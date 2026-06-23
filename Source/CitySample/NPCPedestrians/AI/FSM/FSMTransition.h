#pragma once
#include "CoreMinimal.h"

class UFSMState;

class CITYSAMPLE_API FSMTransition
{
public:

	FSMTransition(const UFSMState* toState, UWorld* world) : _ToState{ toState }, _World{ world } {}
	virtual ~FSMTransition() {}

	virtual bool Evaluate(float deltaTime) const { return false; }
	const UFSMState* GetToState() const { return _ToState; }

protected:

	const UFSMState* _ToState;
	UWorld* _World{};

};
