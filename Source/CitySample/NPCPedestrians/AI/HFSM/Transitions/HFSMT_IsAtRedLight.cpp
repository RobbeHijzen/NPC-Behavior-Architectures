#include "HFSMT_IsAtRedLight.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

bool HFSMT_IsAtRedLight::Evaluate(float deltaTime) const
{
	if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		if (_Inverse)
		{
			return moveComp->IsCurrentLaneWalkable();
		}
		else
		{
			return !moveComp->IsCurrentLaneWalkable();
		}
	}

	if (_Inverse)
	{
		return true;
	}
	return false;
}
