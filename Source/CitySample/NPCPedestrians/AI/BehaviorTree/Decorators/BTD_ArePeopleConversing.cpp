#include "BTD_ArePeopleConversing.h"
#include "AIController.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "../../../Pedestrians/ConversationSubsystem.h"
#include "../../../Pedestrians/Pedestrian.h"

bool UBTD_ArePeopleConversing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return EBTNodeResult::Failed;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;

	APedestrian* ownerPedestrian = Cast<APedestrian>(pawn);
	if (!ownerPedestrian) return EBTNodeResult::Failed;

	TArray<AActor*> actors{};
	GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(ownerPedestrian->GetActorLocation(), 1000.f, actors);
	auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();

	for (auto actor : actors)
	{
		if (conversationSubsystem->HasActiveToken(actor))
		{
			FTransform transform{};
			transform.SetLocation(ownerPedestrian->GetActorLocation() + 0.9 * (actor->GetActorLocation() - ownerPedestrian->GetActorLocation()));
			transform.SetRotation((FRotator{ actor->GetActorRotation() - ownerPedestrian->GetActorRotation() }).Quaternion());

			ownerPedestrian->SetConfrontTransform(transform);

			return true;
		}
	}

	return false;
}
