#pragma once

#include "CoreMinimal.h"
#include "../HFSMState.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "HFSMS_Flee.generated.h"

UCLASS()
class CITYSAMPLE_API UHFSMS_Flee : public UHFSMState
{
	GENERATED_BODY()

public:

	void BeginPlay(APawn* pawn, UWorld* world) override;

	void EnterState(APawn* pawn, UWorld* world) override;

	const std::type_info& GetType() const override
	{
		return typeid(UHFSMS_Flee);
	}

private:

	APedestrian* _Pedestrian{};
};
