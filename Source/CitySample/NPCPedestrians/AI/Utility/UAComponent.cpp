#include "UAComponent.h"
#include "AIController.h"

#include "States/UAS_Wander.h"
#include "States/UAS_Idle.h"
#include "States/UAS_Flee.h"
#include "States/UAS_React.h"
#include "States/UAS_Converse.h"
#include "States/UAS_Shop.h"
#include "States/UAS_WindowShop.h"
#include "States/UAS_Work.h"
#include "States/UAS_Wait.h"
#include "States/UAS_Sit.h"

#include "States/UAS_Confronting.h"
#include "States/UAS_Cowering.h"
#include "States/UAS_Evading.h"
#include "States/UAS_Following.h"
#include "States/UAS_Investigating.h"
#include "States/UAS_Photographing.h"
#include "States/UAS_Reporting.h"
#include "States/UAS_Spectating.h"

void UUAComponent::BeginPlay()
{
	Super::BeginPlay();

	switch (_ComplexityLevel)
	{
	case UAComplexityLevel::Simple:
	{
		_States.Add(NewObject<UUAS_Wander>(this));
		_States.Add(NewObject<UUAS_Idle>(this));
		_States.Add(NewObject<UUAS_Flee>(this));
		_States.Add(NewObject<UUAS_React>(this));

		break;
	}
	case UAComplexityLevel::Medium:
	{
		_States.Add(NewObject<UUAS_Wander>(this));
		_States.Add(NewObject<UUAS_Idle>(this));
		_States.Add(NewObject<UUAS_Flee>(this));
		_States.Add(NewObject<UUAS_React>(this));
		_States.Add(NewObject<UUAS_Converse>(this));
		_States.Add(NewObject<UUAS_Shop>(this));
		_States.Add(NewObject<UUAS_WindowShop>(this));
		_States.Add(NewObject<UUAS_Work>(this));
		_States.Add(NewObject<UUAS_Wait>(this));
		_States.Add(NewObject<UUAS_Sit>(this));

		break;
	}
	case UAComplexityLevel::High:
	{
		_States.Add(NewObject<UUAS_Wander>(this));
		_States.Add(NewObject<UUAS_Idle>(this));
		_States.Add(NewObject<UUAS_Flee>(this));
		_States.Add(NewObject<UUAS_React>(this));
		_States.Add(NewObject<UUAS_Converse>(this));
		_States.Add(NewObject<UUAS_Shop>(this));
		_States.Add(NewObject<UUAS_WindowShop>(this));
		_States.Add(NewObject<UUAS_Work>(this));
		_States.Add(NewObject<UUAS_Wait>(this));
		_States.Add(NewObject<UUAS_Sit>(this));

		_States.Add(NewObject<UUAS_Confronting>(this));
		_States.Add(NewObject<UUAS_Cowering>(this));
		_States.Add(NewObject<UUAS_Evading>(this));
		_States.Add(NewObject<UUAS_Following>(this));
		_States.Add(NewObject<UUAS_Investigating>(this));
		_States.Add(NewObject<UUAS_Photographing>(this));
		_States.Add(NewObject<UUAS_Reporting>(this));
		_States.Add(NewObject<UUAS_Spectating>(this));


		break;
	}
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			if (auto AIController = Cast<AAIController>(GetOwner()))
			{
				_PedestrianReference = Cast<APedestrian>(AIController->GetPawn());
			}
			if (!_PedestrianReference->IsValidLowLevel()) return;


			for (auto& state : _States)
			{
				auto world{ GetWorld() };
				state->BeginPlay(_PedestrianReference, world);
			}

			this->_CurrentStateIndex = 0;

			if (_States.IsValidIndex(_CurrentStateIndex))
			{
				_States[_CurrentStateIndex]->EnterState(_PedestrianReference, GetWorld());
			}

		});
}


void UUAComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	_CurrentTickTime += DeltaTime;

	if (_CurrentTickTime >= _TickInterval)
	{
		_CurrentTickTime = 0.f;
		Super::TickComponent(_TickInterval, TickType, ThisTickFunction);

		TRACE_CPUPROFILER_EVENT_SCOPE_STR("UA_Time");


		float maxValue{};
		int maxValueIndex{ -1 };

		if(_States.IsValidIndex(_CurrentStateIndex))
			_States[_CurrentStateIndex]->TickState(_TickInterval, _PedestrianReference);

		for (int index{}; index < _States.Num(); ++index)
		{

			float value = _States[index]->UtilityFunction(_PedestrianReference);
			if (index == _CurrentStateIndex) value *= 1.25f;
				
			if (value > maxValue)
			{
				maxValue = value;
				maxValueIndex = index;
			}

		}

		if (maxValueIndex != _CurrentStateIndex && _States.IsValidIndex(maxValueIndex))
		{
			_States[_CurrentStateIndex]->ExitState(_PedestrianReference);
			_States[maxValueIndex]->EnterState(_PedestrianReference, GetWorld());
			_CurrentStateIndex = maxValueIndex;
		}

	}
	
}

