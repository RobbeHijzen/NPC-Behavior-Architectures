#include "HFSMS_Root.h"

void UHFSMS_Root::EnterState(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);
}

void UHFSMS_Root::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);
}