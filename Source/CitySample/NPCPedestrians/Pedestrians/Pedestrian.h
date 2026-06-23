#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Pedestrian.generated.h"

UENUM(BlueprintType)
enum class EAnimationType : uint8
{
	Idle,
	Walking,
	Running,
	Reacting,
	Sitting,
	Cower,
	PhoneCall
};

UCLASS()
class CITYSAMPLE_API APedestrian : public APawn
{
	GENERATED_BODY()

public:

	APedestrian();
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetAnimation(EAnimationType animationType, bool loop);

	UFUNCTION(BlueprintCallable)
	float GetAnimationLength(EAnimationType animationType);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* _Capsule{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* _SkeletalMesh{};

	UFUNCTION(BlueprintCallable)
	float GetData(FString dataName) const 
	{ 
		if (auto value = _Data.Find(dataName))
			return *value;

		return 0.f; 
	}

	UFUNCTION(BlueprintCallable)
	float AddToData(FString dataName, float valueToAdd) 
	{
		if (auto value = _Data.Find(dataName))
		{
			*value = FMath::Clamp(*value + valueToAdd * _RandomDataMultiplier, 0.f, 1.f);
			return *value;
		}

		return 0.f;
	}

	UFUNCTION(BlueprintCallable)
	void SetSuspicionLocation(FVector location) { _SuspicionLocation = location; }

	UFUNCTION(BlueprintCallable)
	FVector GetSuspicionLocation() const { return _SuspicionLocation; }

	UFUNCTION(BlueprintCallable)
	int GetFriendGroup() const { return _FriendGroupNumber; }

	UFUNCTION(BlueprintCallable)
	APedestrian* GetClosestFriend() const { return _ClosestFriend; }

	UFUNCTION(BlueprintCallable)
	void SetClosestFriend(APedestrian* closestFriend) { _ClosestFriend = closestFriend; }

	UFUNCTION(BlueprintCallable)
	FTransform GetConfrontTransform() const { return _ToConfrontTransform; }

	UFUNCTION(BlueprintCallable)
	void SetConfrontTransform(FTransform newTransform) { _ToConfrontTransform = newTransform; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPedestrianMovementComponent* _PedestrianMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPedestrianSmartObjectUserComp* _PedestrianSmartObjectUserComponent{};
	
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _IdleAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _WalkingAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _RunningAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _ReactingAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _SitAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _CowerAnimation{};

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UAnimationAsset> _PhoneCallAnimation{};

	TMap<FString, float> _Data =
	{
		{"Fatigue", 0.f},
		{"Threat", 0.f},
		{"SocialNeed", 0.f},
		{"Suspicion", 0.f}
	};

	FVector _SuspicionLocation{};

	float _RandomDataMultiplier{};

	int _FriendGroupNumber{};
	APedestrian* _ClosestFriend{};

	FTransform _ToConfrontTransform{};
};
