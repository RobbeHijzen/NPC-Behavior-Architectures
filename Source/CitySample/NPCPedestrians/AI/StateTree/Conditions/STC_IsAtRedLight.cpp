#include "STC_IsAtRedLight.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

bool FSTC_IsAtRedLight::TestCondition(FStateTreeExecutionContext& Context) const
{
	FIsAtRedLightTaskInstanceData& data = Context.GetInstanceData(*this);
	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		if (data.Inverse)
		{
			return moveComp->IsCurrentLaneWalkable();
		}
		else
		{
			return !moveComp->IsCurrentLaneWalkable();
		}
	}

	if (data.Inverse)
	{
		return true;
	}
	return false;
}
