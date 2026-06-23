#include "ConversationSubsystem.h"
#include "NPCSpatialGrid.h"
#include "Pedestrian.h"

FConversationToken* UConversationSubsystem::TryStartConversation(AActor* Initiator, float SearchRadius)
{
	auto spatialGrid = GetWorld()->GetSubsystem<UNPCSpatialGrid>();

	if (spatialGrid)
	{
		TArray<AActor*> nearbyActors{};
		spatialGrid->QueryRadius(Initiator->GetActorLocation(), SearchRadius, nearbyActors);

		float highestSocialNeed{ 0.f };
		AActor* highestActor{};

		for (auto other : nearbyActors)
		{
			if (other == Initiator)
			{
				continue;
			}

			if (auto pedestrian = Cast<APedestrian>(other))
			{
				float socialNeed = pedestrian->GetData("SocialNeed");
				if (socialNeed > highestSocialNeed)
				{
					highestSocialNeed = socialNeed;
					highestActor = pedestrian;
				}
			}

		}

		if (highestActor)
		{
			FConversationToken newToken{};
			newToken.Initiator = Initiator;
			newToken.Responder = highestActor;
			newToken.Duration = FMath::FRandRange(10.f, 20.f);
			newToken.MeetingLocation = (highestActor->GetActorLocation() + Initiator->GetActorLocation()) / 2.f;

			auto index = _ActiveTokens.Emplace(newToken);

			return &_ActiveTokens[index];
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

void UConversationSubsystem::AcceptConversation(AActor* Responder, FConversationToken* Token)
{
	if (Token && Token->Responder == Responder)
	{
		Token->bResponderAccepted = true;
	}
}

void UConversationSubsystem::EndConversation(FConversationToken* Token)
{
	if (Token)
	{
		Token->bConversationEnding = true;
	}
}

bool UConversationSubsystem::HasActiveToken(AActor* actor)
{
	for (auto& token : _ActiveTokens)
	{
		if (token.Responder == actor || token.Initiator == actor)
		{
			return true;
		}
	}
	return false;
}

FConversationToken* UConversationSubsystem::GetPendingInvite(AActor* Actor)
{
	for (auto& token : _ActiveTokens)
	{
		if (token.Responder == Actor && token.bResponderAccepted == false)
		{
			return &token;
		}
	}

	return nullptr;
}
