#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../../Pedestrians/Pedestrian.h"

#include "UAState.generated.h"

UENUM(BlueprintType)
enum class UAComplexityLevel : uint8
{
	Simple UMETA(DisplayName = "Simple"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High")
};

UCLASS()
class CITYSAMPLE_API UUAState : public UObject
{
	GENERATED_BODY()
	
public:

	UUAState() {}
	virtual ~UUAState() {}

	virtual void BeginPlay(APedestrian* pedestrian, UWorld* world) {}

	virtual void EnterState(APedestrian* pedestrian, UWorld* world) {}
	virtual void TickState(float deltaTime, APedestrian* pedestrian) {}
	virtual void ExitState(APedestrian* pedestrian) {}

	virtual float UtilityFunction(APedestrian* pedestrian) { return 0.f; }

	//void SetOwnerComponent(const UUAComponent* ownerComponent) { _OwnerComponent = ownerComponent; }

protected:

	//const UUAComponent* _OwnerComponent{};


};
