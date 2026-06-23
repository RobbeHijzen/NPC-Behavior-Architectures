#include "AIC_BT_Base.h"
#include "BTComponentCustom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "VisualLogger/VisualLoggerTypes.h"
#include "VisualLogger/VisualLogger.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "DisplayDebugHelpers.h"
#include "ProfilingDebugging/CsvProfiler.h"

void AAIC_BT_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (_BehaviorTree == NULL)
	{
		UE_VLOG(this, LogBehaviorTree, Warning, TEXT("RunBehaviorTree: Unable to run NULL behavior tree"));
		return;
	}

	bool bSuccess = true;

	// see if need a blackboard component at all
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (_BehaviorTree->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(_BehaviorTree->BlackboardAsset) == false))
	{
		bSuccess = UseBlackboard(_BehaviorTree->BlackboardAsset, BlackboardComp);
	}

	if (bSuccess)
	{
		UBTComponentCustom* BTComp = Cast<UBTComponentCustom>(BrainComponent);
		if (BTComp == NULL)
		{
			UE_VLOG(this, LogBehaviorTree, Log, TEXT("RunBehaviorTree: spawning BehaviorTreeComponent.."));

			BTComp = NewObject<UBTComponentCustom>(this);
			BTComp->RegisterComponent();
			REDIRECT_OBJECT_TO_VLOG(BTComp, this);
		}

		// make sure BrainComponent points at the newly created BT component
		BrainComponent = BTComp;

		check(BTComp != NULL);
		BTComp->StartTree(*_BehaviorTree, EBTExecutionMode::Looped);
	}
}