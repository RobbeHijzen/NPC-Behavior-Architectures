#include "BTD_HasPendingConversation.h"
#include "../../../Pedestrians/ConversationSubsystem.h"
#include "AIController.h"

bool UBTD_HasPendingConversation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return false;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return false;

	auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();
	if (conversationSubsystem)
	{
		auto token = conversationSubsystem->GetPendingInvite(pawn);
		if (token)
		{
			return true;
		}
	}
	return false;
}
