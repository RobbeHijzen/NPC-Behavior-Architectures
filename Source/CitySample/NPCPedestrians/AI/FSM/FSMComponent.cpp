#include "FSMComponent.h"
#include "AIController.h"

#include "States/FSMS_Wander.h"
#include "States/FSMS_Idle.h"
#include "States/FSMS_Flee.h"
#include "States/FSMS_React.h"

#include "States/FSMS_Work.h"
#include "States/FSMS_Shop.h"
#include "States/FSMS_WindowShop.h"
#include "States/FSMT_Sit.h"
#include "States/FSMS_Converse.h"
#include "States/FSMS_Wait.h"

#include "States/FSMS_Investigating.h"
#include "States/FSMS_Photographing.h"
#include "States/FSMS_Confronting.h"
#include "States/FSMS_Cowering.h"
#include "States/FSMS_Evading.h"
#include "States/FSMS_Spectating.h"
#include "States/FSMS_Reporting.h"
#include "States/FSMS_Following.h"

void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	switch (_FSMComplexityLevel)
	{
	case FSMComplexityLevel::Simple:
	{
		_States.Add(NewObject<UFSMS_Wander>(this));
		_States.Add(NewObject<UFSMS_Idle>(this));
		_States.Add(NewObject<UFSMS_Flee>(this));
		_States.Add(NewObject<UFSMS_React>(this));

		break;
	}
	case FSMComplexityLevel::Medium:
	{
		_States.Add(NewObject<UFSMS_Wander>(this));
		_States.Add(NewObject<UFSMS_Idle>(this));
		_States.Add(NewObject<UFSMS_Flee>(this));
		_States.Add(NewObject<UFSMS_React>(this));
								   
		_States.Add(NewObject<UFSMT_Sit>(this));
		_States.Add(NewObject<UFSMS_Shop>(this));
		_States.Add(NewObject<UFSMS_WindowShop>(this));
		_States.Add(NewObject<UFSMS_Work>(this));
		_States.Add(NewObject<UFSMS_Wait>(this));
		_States.Add(NewObject<UFSMS_Converse>(this));

		break;
	}
	case FSMComplexityLevel::High:
	{
		_States.Add(NewObject<UFSMS_Wander>(this));
		_States.Add(NewObject<UFSMS_Idle>(this));
		_States.Add(NewObject<UFSMS_Flee>(this));
		_States.Add(NewObject<UFSMS_React>(this));

		_States.Add(NewObject<UFSMT_Sit>(this));
		_States.Add(NewObject<UFSMS_Shop>(this));
		_States.Add(NewObject<UFSMS_WindowShop>(this));
		_States.Add(NewObject<UFSMS_Work>(this));
		_States.Add(NewObject<UFSMS_Wait>(this));
		_States.Add(NewObject<UFSMS_Converse>(this));

		_States.Add(NewObject<UFSMS_Confronting>(this));
		_States.Add(NewObject<UFSMS_Cowering>(this));
		_States.Add(NewObject<UFSMS_Evading>(this));
		_States.Add(NewObject<UFSMS_Following>(this));
		_States.Add(NewObject<UFSMS_Investigating>(this));
		_States.Add(NewObject<UFSMS_Photographing>(this));
		_States.Add(NewObject<UFSMS_Reporting>(this));
		_States.Add(NewObject<UFSMS_Spectating>(this));


		break;
	}
	}


	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			if (auto AIController = Cast<AAIController>(GetOwner()))
			{
				_PawnReference = AIController->GetPawn();
			}
			if (!_PawnReference->IsValidLowLevel()) return;


			for (auto& state : _States)
			{
				state->SetOwnerComponent(this);

				auto world{ GetWorld() };
				state->BeginPlay(_PawnReference, world);
			}

			this->_CurrentStateIndex = 0;

			if (_States.IsValidIndex(_CurrentStateIndex))
			{
				_States[_CurrentStateIndex]->EnterState(_PawnReference, GetWorld());
			}

		});
}

void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	_CurrentTickTime += DeltaTime;

	if (_CurrentTickTime >= _TickInterval)
	{
		_CurrentTickTime = 0.f;
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		TRACE_CPUPROFILER_EVENT_SCOPE_STR("FSM_Time");

		if (_States.IsValidIndex(_CurrentStateIndex))
		{
			auto& state{ _States[_CurrentStateIndex] };
			if (state->IsValidLowLevel())
			{
				state->TickState(_TickInterval, _PawnReference);

				for (auto& transition : _States[_CurrentStateIndex]->GetTransitions())
				{
					if (transition->Evaluate(_TickInterval))
					{
						if (ChangeState(transition->GetToState()))
						{
							break;
						}
					}
				}
			}
		}
	}
}

bool UFSMComponent::ChangeState(const UFSMState* newState)
{
	int32 newStateIndex{ 0 };

	for (const auto& state : _States)
	{
		if (state == newState)
		{
			_States[_CurrentStateIndex]->ExitState(_PawnReference);
			_States[newStateIndex]->EnterState(_PawnReference, GetWorld());
			_CurrentStateIndex = newStateIndex;

			return true;
		}

		++newStateIndex;
	}
	return false;
}



