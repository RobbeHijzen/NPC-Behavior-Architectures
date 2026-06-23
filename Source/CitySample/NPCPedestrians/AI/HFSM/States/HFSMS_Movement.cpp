#include "HFSMS_Movement.h"
#include "../Transitions/HFSMT_CheckData.h"
#include "../HFSMComponent.h"
#include "HFSMS_Flee.h"
#include "HFSMS_React.h"

void UHFSMS_Movement::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
	AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));
}