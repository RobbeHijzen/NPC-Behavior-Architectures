#pragma once

#include "CoreMinimal.h"
#include "../FSMState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "FSMS_Evading.generated.h"


UCLASS()
class CITYSAMPLE_API UFSMS_Evading : public UFSMState
{
	GENERATED_BODY()
public:

	void BeginPlay(APawn* pawn, UWorld* world) override;

	void EnterState(APawn* pawn, UWorld* world) override;
	void TickState(float deltaTime, APawn* pawn) override;

	const std::type_info& GetType() const override
	{
		return typeid(UFSMS_Evading);
	}

private:

	APedestrian* _Pedestrian{};
	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ 0.05f };
	float _SuspicionChange{ -0.1f };

};
