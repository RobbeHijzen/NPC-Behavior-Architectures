#include "HFSMState.h"

void UHFSMState::AddTransition(HFSMTransition* transition)
{
	_Transitions.Add(TUniquePtr<HFSMTransition>(transition));
}
