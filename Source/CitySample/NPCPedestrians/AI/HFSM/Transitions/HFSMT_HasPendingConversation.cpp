#include "HFSMT_HasPendingConversation.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

bool HFSMT_HasPendingConversation::Evaluate(float deltaTime) const
{
	auto conversationSubsystem = _World->GetSubsystem<UConversationSubsystem>();
	if (conversationSubsystem)
	{
		auto token = conversationSubsystem->GetPendingInvite(_Pedestrian);
		if (token)
		{
			return true;
		}
	}
	return false;
}
