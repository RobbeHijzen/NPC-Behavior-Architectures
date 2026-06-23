#pragma once

#include "CoreMinimal.h"
#include "../UAState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"
#include "UAS_Sit.generated.h"


UCLASS()
class CITYSAMPLE_API UUAS_Sit : public UUAState
{
	GENERATED_BODY()
public:
	void BeginPlay(APedestrian* pedestrian, UWorld* world) override;

	void EnterState(APedestrian* pedestrian, UWorld* world) override;
	void TickState(float deltaTime, APedestrian* pedestrian) override;

	float UtilityFunction(APedestrian* pedestrian) override;

private:

	APedestrian* _PedestrianReference{};
	UPedestrianSmartObjectUserComp* _PedestrianSmartObj{};

	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ 0.05f };
	float _FatigueChange{ -0.1f };
	float _SuspicionChange{ -0.1f };

};
