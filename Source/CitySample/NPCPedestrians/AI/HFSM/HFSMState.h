#pragma once

#include "CoreMinimal.h"
#include "HFSMTransition.h"
#include <typeinfo>

#include "HFSMState.generated.h"


class UHFSMComponent;

UENUM(BlueprintType)
enum class HFSMComplexityLevel : uint8
{
	Simple UMETA(DisplayName = "Simple"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High")
};

UCLASS()
class CITYSAMPLE_API UHFSMState : public UObject
{
	GENERATED_BODY()

public:

	UHFSMState() {}
	virtual ~UHFSMState() {}
	void Initialize(UHFSMState* parentState) { _ParentState = parentState; }

	virtual void BeginPlay(APawn* pawn, UWorld* world) {};

	virtual void EnterState(APawn* pawn, UWorld* world) {};
	virtual void TickState(float deltaTime, APawn* pawn) {};
	virtual void ExitState(APawn* pawn) {};

	virtual const std::type_info& GetType() const { return typeid(UHFSMState); };

	TArray<const HFSMTransition*> GetTransitions() const
	{
		TArray<const HFSMTransition*> arr{};
		for (const auto& transition : _Transitions)
		{
			arr.Add(transition.Get());
		}
		return arr;
	}

	UHFSMState* GetParentState() const { return _ParentState; }

	void SetOwnerComponent(const UHFSMComponent* ownerComponent) { _OwnerComponent = ownerComponent; }

protected:

	void AddTransition(HFSMTransition* transition);
	void SetParentState(UHFSMState* newParentState) { _ParentState = newParentState; }

	const UHFSMComponent* _OwnerComponent{};

private:

	TArray<TUniquePtr<HFSMTransition>> _Transitions{};
	UHFSMState* _ParentState{};

};
