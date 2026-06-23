#include "HFSMT_RandomChanceSmartObject.h"

bool HFSMT_RandomChanceSmartObject::Evaluate(float deltaTime) const
{
	if (FMath::FRand() <= _RandomChancePerSecond * deltaTime)
	{
		if (auto userComp = _Pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>())
		{
			return userComp->HasNeabySmartObject(_SmartObjectTag, _Radius);
		}
	}

	return false;
}
