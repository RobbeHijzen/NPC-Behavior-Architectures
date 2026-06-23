#pragma once

#include "CoreMinimal.h"
#include "../HFSMState.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "HFSMS_Idle.generated.h"

UCLASS()
class CITYSAMPLE_API UHFSMS_Idle : public UHFSMState
{
	GENERATED_BODY()

public:

	void BeginPlay(APawn* pawn, UWorld* world) override;

	void EnterState(APawn* pawn, UWorld* world) override;
	void TickState(float deltaTime, APawn* pawn) override;

	const std::type_info& GetType() const override
	{
		return typeid(UHFSMS_Idle);
	}

private:

	APedestrian* _Pedestrian{};
	float _FatigueChange{ -0.2 };
};
