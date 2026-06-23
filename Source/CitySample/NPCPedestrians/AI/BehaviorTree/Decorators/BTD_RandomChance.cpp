#include "BTD_RandomChance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

bool UBTD_RandomChance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* bb = OwnerComp.GetBlackboardComponent();
	if (bb)
	{
		bool didRandomChanceSucceed{};
		if (_UseDeltaTime)
			didRandomChanceSucceed = FMath::FRand() <= _ChancePerSecond * 0.25f;

		else
			didRandomChanceSucceed = FMath::FRand() <= _ChancePerSecond;

		bb->SetValueAsBool(TEXT("RandomChanceSucceeded"), didRandomChanceSucceed);

		return didRandomChanceSucceed;
	}

	return false;
}

void UBTD_RandomChance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return;

	UBlackboardComponent* bb = OwnerComp.GetBlackboardComponent();

	if (bb)
	{
		bool didRandomChanceSucceed{};
		if (_UseDeltaTime)
			didRandomChanceSucceed = FMath::FRand() <= _ChancePerSecond * 0.25f;

		else
			didRandomChanceSucceed = FMath::FRand() <= _ChancePerSecond;

		bb->SetValueAsBool(TEXT("RandomChanceSucceeded"), didRandomChanceSucceed);
	}

}
