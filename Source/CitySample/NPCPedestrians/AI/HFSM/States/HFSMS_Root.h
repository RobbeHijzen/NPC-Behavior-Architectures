#pragma once

#include "CoreMinimal.h"
#include "../HFSMState.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "HFSMS_Root.generated.h"

UCLASS()
class CITYSAMPLE_API UHFSMS_Root : public UHFSMState
{
	GENERATED_BODY()

public:

	void EnterState(APawn* pawn, UWorld* world) override;
	void TickState(float deltaTime, APawn* pawn) override;

	const std::type_info& GetType() const override
	{
		return typeid(UHFSMS_Root);
	}

private:

	APedestrian* _Pedestrian{};
	float _ThreatChange{ -0.1 };
	float _SocialNeedChange{ 0.05f };
	float _SuspicionChange{ -0.1f };
};
