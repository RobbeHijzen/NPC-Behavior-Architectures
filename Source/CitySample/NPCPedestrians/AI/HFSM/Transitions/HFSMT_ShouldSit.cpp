#include "HFSMT_ShouldSit.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"
#include "GameplayTagsManager.h"

bool HFSMT_ShouldSit::Evaluate(float deltaTime) const
{
	if (_Pedestrian->GetData("Fatigue") >= 0.65f)
	{
		if (auto userComp = _Pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>())
		{
			return userComp->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Seat"), 3000.f);
		}
	}

	return false;
}