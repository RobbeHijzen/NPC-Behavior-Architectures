#include "STC_ArePeopleConversing.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "../../../Pedestrians/ConversationSubsystem.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "StateTreeExecutionContext.h"

bool FSTC_ArePeopleConversing::TestCondition(FStateTreeExecutionContext& Context) const
{
	FArePeopleConversingTaskInstanceData& data = Context.GetInstanceData(*this);

	APedestrian* ownerPedestrian{ Cast<APedestrian>(data.Actor) };

	TArray<AActor*> actors{};
	Context.GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(data.Actor->GetActorLocation(), 1000.f, actors);
	auto conversationSubsystem = Context.GetWorld()->GetSubsystem<UConversationSubsystem>();

	for (auto actor : actors)
	{
		if (conversationSubsystem->HasActiveToken(actor))
		{
			FTransform transform{};
			transform.SetLocation(ownerPedestrian->GetActorLocation() + 0.9 * (actor->GetActorLocation() - ownerPedestrian->GetActorLocation()));
			transform.SetRotation((FRotator{ actor->GetActorRotation() - ownerPedestrian->GetActorRotation()}).Quaternion());

			ownerPedestrian->SetConfrontTransform(transform);

			return true;
		}
	}

	return false;
}
