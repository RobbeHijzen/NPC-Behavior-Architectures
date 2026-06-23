#include "FSMT_HasFriendNearby.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

bool FSMT_HasFriendNearby::Evaluate(float deltaTime) const
{
	if (FMath::FRand() <= _RandomChancePerSecond * deltaTime)
	{
		int friendGroup{ _Pedestrian->GetFriendGroup() };

		TArray<AActor*> actors{};
		_World->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(_Pedestrian->GetActorLocation(), 1000.f, actors);

		for (auto actor : actors)
		{
			if (actor == _Pedestrian) continue;

			if (auto pedestrian = Cast<APedestrian>(actor))
			{
				if (friendGroup == pedestrian->GetFriendGroup())
				{
					_Pedestrian->SetClosestFriend(pedestrian);
					return true;
				}
			}
		}
	}

	return false;
}
