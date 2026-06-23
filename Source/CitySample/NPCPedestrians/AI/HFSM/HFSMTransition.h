#pragma once

#include "CoreMinimal.h"

class UHFSMState;

class CITYSAMPLE_API HFSMTransition
{
public:

	HFSMTransition(const UHFSMState* toState, UWorld* world) : _ToState{ toState }, _World{ world } {}
	virtual ~HFSMTransition() {}

	virtual bool Evaluate(float deltaTime) const { return false; }
	const UHFSMState* GetToState() const { return _ToState; }


protected:

	const UHFSMState* _ToState;
	UWorld* _World{};

};
