#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FSMTransition.h"
#include <typeinfo>

#include "FSMState.generated.h"

class UFSMComponent;

UENUM(BlueprintType)
enum class FSMComplexityLevel : uint8
{
	Simple UMETA(DisplayName = "Simple"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High")
};

UCLASS()
class CITYSAMPLE_API UFSMState : public UObject
{
	GENERATED_BODY()

public:

	UFSMState() {}
	virtual ~UFSMState() {}

	virtual void BeginPlay(APawn* pawn, UWorld* world) {}

	virtual void EnterState(APawn* pawn, UWorld* world) {}
	virtual void TickState(float deltaTime, APawn* pawn) {}
	virtual void ExitState(APawn* pawn) {}

	virtual const std::type_info& GetType() const { return typeid(UFSMState); };

	TArray<const FSMTransition*> GetTransitions()
	{
		TArray<const FSMTransition*> arr{};
		for (const auto& transition : _Transitions)
		{
			arr.Add(transition.Get());
		}
		return arr;
	}

	void SetOwnerComponent(const UFSMComponent* ownerComponent) { _OwnerComponent = ownerComponent; }

protected:

	void AddTransition(FSMTransition* transition);

	const UFSMComponent* _OwnerComponent{};

private:

	TArray<TUniquePtr<FSMTransition>> _Transitions{};

};

