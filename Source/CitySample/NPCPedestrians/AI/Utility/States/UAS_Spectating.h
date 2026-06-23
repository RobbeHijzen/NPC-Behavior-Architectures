#pragma once

#include "CoreMinimal.h"
#include "../UAState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "UAS_Spectating.generated.h"


UCLASS()
class CITYSAMPLE_API UUAS_Spectating : public UUAState
{
	GENERATED_BODY()
public:

	void EnterState(APedestrian* pedestrian, UWorld* world) override;
	void TickState(float deltaTime, APedestrian* pedestrian) override;

	float UtilityFunction(APedestrian* pedestrian) override;

private:

	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ 0.05f };
	float _SuspicionChange{ -0.1f };

};
