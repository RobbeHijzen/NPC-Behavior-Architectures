#include "STC_HasPendingConversation.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

bool FSTC_HasPendingConversation::TestCondition(FStateTreeExecutionContext& Context) const
{
	auto conversationSubsystem = Context.GetWorld()->GetSubsystem<UConversationSubsystem>();
	if (conversationSubsystem)
	{
		FConverseInstanceData& data = Context.GetInstanceData(*this);

		auto token = conversationSubsystem->GetPendingInvite(data.Actor);
		if (token)
		{
			return true;
		}
	}
	return false;
}
