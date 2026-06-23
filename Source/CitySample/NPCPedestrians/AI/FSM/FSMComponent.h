#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSMState.h"
#include "FSMTransition.h"

#include "FSMComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSAMPLE_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFSMComponent() { PrimaryComponentTick.bCanEverTick = true; }
	virtual void BeginPlay() override;

	template<typename T>
	const UFSMState* GetStateOfClass() const
	{
		for (const UFSMState* State : _States)
		{
			if (State->GetType() == typeid(T))
			{
				return static_cast<const T*>(State);
			}
		}
		return nullptr;
	}
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FSMComplexityLevel GetComplexityLevel() const { return _FSMComplexityLevel; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSMComplexityLevel _FSMComplexityLevel{ FSMComplexityLevel::Simple };

private:

	UPROPERTY()
	TArray<TObjectPtr<UFSMState>> _States{};
	int _CurrentStateIndex{ -1 };
	TObjectPtr<APawn> _PawnReference{};

	bool ChangeState(const UFSMState* newState);


	float _TickInterval{ 0.25f };
	float _CurrentTickTime{};
};
