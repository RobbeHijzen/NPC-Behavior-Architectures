#include "STC_HasFriendNearby.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/Pedestrian.h"

bool FSTC_HasFriendNearby::TestCondition(FStateTreeExecutionContext& Context) const
{
	FTaskInstanceData& data = Context.GetInstanceData(*this);

	APedestrian* ownerPedestrian{ Cast<APedestrian>(data.Actor) };
	int friendGroup{ ownerPedestrian->GetFriendGroup()};

	TArray<AActor*> actors{};
	Context.GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(data.Actor->GetActorLocation(), 200.f, actors);

	for (auto actor : actors)
	{
		if (actor == ownerPedestrian) continue;

		if (auto pedestrian = Cast<APedestrian>(actor))
		{
			if (friendGroup == pedestrian->GetFriendGroup())
			{
				ownerPedestrian->SetClosestFriend(pedestrian);
				return true;
			}
		}
	}

	return false;
}
