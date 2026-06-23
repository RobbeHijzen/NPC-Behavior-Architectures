#include "STC_HasNearbySmartObject.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"

bool FSTC_HasNearbySmartObject::TestCondition(FStateTreeExecutionContext& Context) const
{
	FSmartObjectInstanceData& data = Context.GetInstanceData(*this);

	if (auto userComp = data.Actor->GetComponentByClass<UPedestrianSmartObjectUserComp>())
	{
		return userComp->HasNeabySmartObject(data.SmartObjectTag, data.Radius);
	}

	return false;
}
