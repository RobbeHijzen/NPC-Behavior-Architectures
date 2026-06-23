#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HFSMState.h"
#include "HFSMTransition.h"

#include "HFSMComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CITYSAMPLE_API UHFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHFSMComponent() { PrimaryComponentTick.bCanEverTick = true; }
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	template<typename T>
	const UHFSMState* GetStateOfClass() const
	{
		for (const UHFSMState* State : _States)
		{
			if (State->GetType() == typeid(T))
			{
				return static_cast<const T*>(State);
			}
		}
		return nullptr;
	}
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	HFSMComplexityLevel GetComplexityLevel() const { return _HFSMComplexityLevel; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	HFSMComplexityLevel _HFSMComplexityLevel{ HFSMComplexityLevel::Simple };

private:

	UPROPERTY()
	TArray<TObjectPtr<UHFSMState>> _States{};
	int _CurrentStateIndex{ 0 };
	TObjectPtr<APawn> _PawnReference{};

	bool ChangeState(const UHFSMState* newState);

	void EnterState(UHFSMState* state);
	void TickState(float deltaTime, UHFSMState* state);
	void ExitState(UHFSMState* state);

	bool EvaluateStateTransitions(float deltaTime, UHFSMState* state);

	float _TickInterval{ 0.25f };
	float _CurrentTickTime{};
};
