#include "FSMT_ArePeopleConversing.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

bool FSMT_ArePeopleConversing::Evaluate(float deltaTime) const
{
	if (FMath::FRand() <= _RandomChancePerSecond * deltaTime)
	{
		TArray<AActor*> actors{};
		_World->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(_Pedestrian->GetActorLocation(), 1000.f, actors);
		auto conversationSubsystem = _World->GetSubsystem<UConversationSubsystem>();

		for (auto actor : actors)
		{
			if (conversationSubsystem->HasActiveToken(actor))
			{
				FTransform transform{};
				transform.SetLocation(_Pedestrian->GetActorLocation() + 0.9 * (actor->GetActorLocation() - _Pedestrian->GetActorLocation()));
				transform.SetRotation((FRotator{ actor->GetActorRotation() - _Pedestrian->GetActorRotation() }).Quaternion());

				_Pedestrian->SetConfrontTransform(transform);

				return true;
			}
		}
	}

	return false;
}
