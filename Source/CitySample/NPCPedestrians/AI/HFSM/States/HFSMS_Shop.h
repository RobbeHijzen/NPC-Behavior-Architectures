#pragma once

#include "CoreMinimal.h"
#include "../HFSMState.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "HFSMS_Shop.generated.h"


UCLASS()
class CITYSAMPLE_API UHFSMS_Shop : public UHFSMState
{
	GENERATED_BODY()
public:

	void BeginPlay(APawn* pawn, UWorld* world) override;

	void EnterState(APawn* pawn, UWorld* world) override;

	const std::type_info& GetType() const override
	{
		return typeid(UHFSMS_Shop);
	}

private:

	APedestrian* _Pedestrian{};
};
