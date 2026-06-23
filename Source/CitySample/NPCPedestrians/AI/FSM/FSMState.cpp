#include "FSMState.h"

void UFSMState::AddTransition(FSMTransition* transition)
{
	_Transitions.Add(TUniquePtr<FSMTransition>(transition));
}