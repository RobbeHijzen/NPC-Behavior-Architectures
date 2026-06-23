#pragma once

#include "CoreMinimal.h"
#include "../UAState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "UAS_Wait.generated.h"


UCLASS()
class CITYSAMPLE_API UUAS_Wait : public UUAState
{
	GENERATED_BODY()
public:
	void BeginPlay(APedestrian* pedestrian, UWorld* world) override;

	void EnterState(APedestrian* pedestrian, UWorld* world) override;
	void TickState(float deltaTime, APedestrian* pedestrian) override;

	float UtilityFunction(APedestrian* pedestrian) override;

private:

	APedestrian* _PedestrianReference{};
	UPedestrianMovementComponent* _PedestrianMoveComp{};

	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ 0.05f };
	float _SuspicionChange{ -0.1f };

};
