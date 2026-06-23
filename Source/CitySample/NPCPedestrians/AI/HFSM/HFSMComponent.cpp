#include "HFSMComponent.h"
#include "AIController.h"

#include "States/HFSMS_Wander.h"
#include "States/HFSMS_Idle.h"
#include "States/HFSMS_Flee.h"
#include "States/HFSMS_React.h"
#include "States/HFSMS_Root.h"
#include "States/HFSMS_Movement.h"

#include "States/HFSMS_Work.h"
#include "States/HFSMS_Shop.h"
#include "States/HFSMS_WindowShop.h"
#include "States/HFSMS_Sit.h"
#include "States/HFSMS_Converse.h"
#include "States/HFSMS_Wait.h"
				 
#include "States/HFSMS_Investigating.h"
#include "States/HFSMS_Photographing.h"
#include "States/HFSMS_Confronting.h"
#include "States/HFSMS_Cowering.h"
#include "States/HFSMS_Evading.h"
#include "States/HFSMS_Spectating.h"
#include "States/HFSMS_Reporting.h"
#include "States/HFSMS_Following.h"

void UHFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	switch (_HFSMComplexityLevel)
	{
	case HFSMComplexityLevel::Simple:
	{
		auto rootState = NewObject<UHFSMS_Root>(this);
		auto movementState = NewObject<UHFSMS_Movement>(this); movementState->Initialize(rootState);

		auto wanderState = NewObject<UHFSMS_Wander>(this); wanderState->Initialize(movementState);
		auto idleState = NewObject<UHFSMS_Idle>(this); idleState->Initialize(movementState);
		auto fleeingState = NewObject<UHFSMS_Flee>(this); fleeingState->Initialize(rootState);
		auto reactingState = NewObject<UHFSMS_React>(this); reactingState->Initialize(rootState);

		_States.Add(wanderState);
		_States.Add(idleState);
		_States.Add(fleeingState);
		_States.Add(reactingState);
		_States.Add(rootState);
		_States.Add(movementState);

		break;
	}
	case HFSMComplexityLevel::Medium:
	{
		auto rootState = NewObject<UHFSMS_Root>(this);
		auto movementState = NewObject<UHFSMS_Movement>(this); movementState->Initialize(rootState);

		auto wanderState = NewObject<UHFSMS_Wander>(this); wanderState->Initialize(movementState);
		auto idleState = NewObject<UHFSMS_Idle>(this); idleState->Initialize(movementState);
		auto fleeingState = NewObject<UHFSMS_Flee>(this); fleeingState->Initialize(rootState);
		auto reactingState = NewObject<UHFSMS_React>(this); reactingState->Initialize(rootState);

		auto sitState = NewObject<UHFSMS_Sit>(this); sitState->Initialize(movementState);
		auto shopState = NewObject<UHFSMS_Shop>(this); shopState->Initialize(movementState);
		auto windowShopState = NewObject<UHFSMS_WindowShop>(this); windowShopState->Initialize(movementState);
		auto workState = NewObject<UHFSMS_Work>(this); workState->Initialize(movementState);
		auto waitState = NewObject<UHFSMS_Wait>(this); waitState->Initialize(movementState);
		auto converseState = NewObject<UHFSMS_Converse>(this); converseState->Initialize(movementState);

		_States.Add(wanderState);
		_States.Add(idleState);
		_States.Add(fleeingState);
		_States.Add(reactingState);

		_States.Add(sitState);
		_States.Add(shopState);
		_States.Add(windowShopState);
		_States.Add(workState);
		_States.Add(waitState);
		_States.Add(converseState);

		_States.Add(rootState);
		_States.Add(movementState);
		break;
	}
	case HFSMComplexityLevel::High:
	{
		auto rootState = NewObject<UHFSMS_Root>(this);
		auto movementState = NewObject<UHFSMS_Movement>(this); movementState->Initialize(rootState);

		auto wanderState = NewObject<UHFSMS_Wander>(this); wanderState->Initialize(movementState);
		auto idleState = NewObject<UHFSMS_Idle>(this); idleState->Initialize(movementState);
		auto fleeingState = NewObject<UHFSMS_Flee>(this); fleeingState->Initialize(rootState);
		auto reactingState = NewObject<UHFSMS_React>(this); reactingState->Initialize(rootState);

		auto sitState = NewObject<UHFSMS_Sit>(this); sitState->Initialize(movementState);
		auto shopState = NewObject<UHFSMS_Shop>(this); shopState->Initialize(movementState);
		auto windowShopState = NewObject<UHFSMS_WindowShop>(this); windowShopState->Initialize(movementState);
		auto workState = NewObject<UHFSMS_Work>(this); workState->Initialize(movementState);
		auto waitState = NewObject<UHFSMS_Wait>(this); waitState->Initialize(movementState);
		auto converseState = NewObject<UHFSMS_Converse>(this); converseState->Initialize(movementState);
							   
		auto confrontingState = NewObject<UHFSMS_Confronting>(this); confrontingState->Initialize(movementState);
		auto coweringState = NewObject<UHFSMS_Cowering>(this); coweringState->Initialize(movementState);
		auto evadingState = NewObject<UHFSMS_Evading>(this); evadingState->Initialize(movementState);
		auto followingState = NewObject<UHFSMS_Following>(this); followingState->Initialize(movementState);
		auto investigatingState = NewObject<UHFSMS_Investigating>(this); investigatingState->Initialize(movementState);
		auto photographingState = NewObject<UHFSMS_Photographing>(this); photographingState->Initialize(movementState);
		auto reportingState = NewObject<UHFSMS_Reporting>(this); reportingState->Initialize(movementState);
		auto spectatingState = NewObject<UHFSMS_Spectating>(this); spectatingState->Initialize(movementState);


		_States.Add(wanderState);
		_States.Add(idleState);
		_States.Add(fleeingState);
		_States.Add(reactingState);

		_States.Add(sitState);
		_States.Add(shopState);
		_States.Add(windowShopState);
		_States.Add(workState);
		_States.Add(waitState);
		_States.Add(converseState);

		_States.Add(confrontingState);
		_States.Add(coweringState);
		_States.Add(evadingState);
		_States.Add(followingState);
		_States.Add(investigatingState);
		_States.Add(photographingState);
		_States.Add(reportingState);
		_States.Add(spectatingState);

		_States.Add(rootState);
		_States.Add(movementState);

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
				state->BeginPlay(_PawnReference, GetWorld());
			}

			this->_CurrentStateIndex = 0;

			if (_States.IsValidIndex(_CurrentStateIndex))
			{
				EnterState(_States[_CurrentStateIndex]);
			}
		});
}

void UHFSMComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	_States.Empty();
}

void UHFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	_CurrentTickTime += DeltaTime;

	if (_CurrentTickTime >= _TickInterval)
	{
		_CurrentTickTime = 0.f;
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		TRACE_CPUPROFILER_EVENT_SCOPE_STR("HFSM_Time");

		if (_States.IsValidIndex(_CurrentStateIndex))
		{
			this->TickState(_TickInterval, _States[_CurrentStateIndex]);
			this->EvaluateStateTransitions(_TickInterval, _States[_CurrentStateIndex]);
		}
	}
}


bool UHFSMComponent::ChangeState(const UHFSMState* newState)
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


void UHFSMComponent::EnterState(UHFSMState* state)
{
	if (auto parentState = state->GetParentState())
	{
		EnterState(parentState);
	}
	state->EnterState(_PawnReference, GetWorld());
}

void UHFSMComponent::TickState(float deltaTime, UHFSMState* state)
{
	if (auto parentState = state->GetParentState())
	{
		if (parentState->IsValidLowLevel())
		{
			TickState(deltaTime, parentState);
		}
	}
	state->TickState(deltaTime, _PawnReference);
}

void UHFSMComponent::ExitState(UHFSMState* state)
{
	if (auto parentState = state->GetParentState())
	{
		ExitState(parentState);
	}
	state->ExitState(_PawnReference);
}

bool UHFSMComponent::EvaluateStateTransitions(float deltaTime, UHFSMState* state)
{
	if (auto parentState = state->GetParentState())
	{
		if (EvaluateStateTransitions(deltaTime, parentState))
		{
			return true;
		}
	}

	for (auto& transition : state->GetTransitions())
	{
		if (transition->Evaluate(deltaTime))
		{
			if (ChangeState(transition->GetToState()))
			{
				return true;
			}
		}
	}

	return false;
}

