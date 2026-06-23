#pragma once

#include "CoreMinimal.h"
#include "../UAState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "UAS_Converse.generated.h"


UCLASS()
class CITYSAMPLE_API UUAS_Converse : public UUAState
{
	GENERATED_BODY()
	
public:
	void BeginPlay(APedestrian* pedestrian, UWorld* world) override;

	void EnterState(APedestrian* pedestrian, UWorld* world) override;
	void ExitState(APedestrian* pedestrian) override;
	void TickState(float deltaTime, APedestrian* pedestrian) override;

	float UtilityFunction(APedestrian* pedestrian) override;

private:

	APedestrian* _PedestrianReference{};

	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ -0.1f };
	float _SuspicionChange{ -0.1f };
	FTimerHandle _ConversationTimerHandle{};

	bool _IsConversing{ false };
};
