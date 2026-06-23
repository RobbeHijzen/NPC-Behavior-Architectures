#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAState.h"
#include "../../Pedestrians/Pedestrian.h"

#include "UAComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSAMPLE_API UUAComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUAComponent() { this->PrimaryComponentTick.bCanEverTick = true; }

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UAComplexityLevel GetComplexityLevel() const { return _ComplexityLevel; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAComplexityLevel _ComplexityLevel{ UAComplexityLevel::Simple };

private:

	UPROPERTY()
	TArray<TObjectPtr<UUAState>> _States{};
	int _CurrentStateIndex{ -1 };
	TObjectPtr<APedestrian> _PedestrianReference{};

	float _TickInterval{ 0.25f };
	float _CurrentTickTime{};
};
