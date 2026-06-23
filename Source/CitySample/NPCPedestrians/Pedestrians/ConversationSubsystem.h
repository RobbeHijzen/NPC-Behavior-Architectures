#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ConversationSubsystem.generated.h"


USTRUCT()
struct FConversationToken
{
    GENERATED_BODY()

    UPROPERTY() AActor* Initiator = nullptr;
    UPROPERTY() AActor* Responder = nullptr;
    UPROPERTY() FVector MeetingLocation = FVector::ZeroVector;
    UPROPERTY() float Duration = 0.f;
    UPROPERTY() bool bConversationEnding = false;
    UPROPERTY() bool bResponderAccepted = false;
};

UCLASS()
class CITYSAMPLE_API UConversationSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public: 

    FConversationToken* TryStartConversation(AActor* Initiator, float SearchRadius);
    void AcceptConversation(AActor* Responder, FConversationToken* Token);
    void EndConversation(FConversationToken* Token);
    bool HasActiveToken(AActor* actor);

    FConversationToken* GetPendingInvite(AActor* Actor);

private:
    TArray<FConversationToken> _ActiveTokens;
};
