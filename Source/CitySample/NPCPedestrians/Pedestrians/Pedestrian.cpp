#include "Pedestrian.h"
#include "PedestrianSmartObjectUserComp.h"
#include "PedestrianMovementComponent.h"

APedestrian::APedestrian()
{
	_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_Capsule->SetupAttachment(GetRootComponent());

	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	_SkeletalMesh->SetupAttachment(_Capsule);

	_PedestrianMovementComponent = CreateDefaultSubobject<UPedestrianMovementComponent>(TEXT("PedestrianMovementComponent"));
	_PedestrianSmartObjectUserComponent = CreateDefaultSubobject<UPedestrianSmartObjectUserComp>(TEXT("PedestrianSmartObjectUserComponent"));
}

void APedestrian::BeginPlay()
{
	Super::BeginPlay();

	_RandomDataMultiplier = FMath::FRand();
	_FriendGroupNumber = FMath::RandRange(0, 25);
}

void APedestrian::SetAnimation(EAnimationType animationType, bool loop)
{
	switch (animationType)
	{
	case EAnimationType::Idle:
	{
		if (_IdleAnimation)
		{
			_SkeletalMesh->PlayAnimation(_IdleAnimation, loop);
		}
		break;
	}
	case EAnimationType::Walking:
	{
		if (_WalkingAnimation)
		{
			_SkeletalMesh->PlayAnimation(_WalkingAnimation, loop);
		}
		break;
	}
	case EAnimationType::Running:
	{
		if (_RunningAnimation)
		{
			_SkeletalMesh->PlayAnimation(_RunningAnimation, loop);
		}
		break;
	}
	case EAnimationType::Reacting:
	{
		if (_ReactingAnimation)
		{
			_SkeletalMesh->PlayAnimation(_ReactingAnimation, loop);
		}
		break;
	}
	case EAnimationType::Sitting:
	{
		if (_SitAnimation)
		{
			_SkeletalMesh->PlayAnimation(_SitAnimation, loop);
		}
		break;
	}
	case EAnimationType::Cower:
	{
		if (_CowerAnimation)
		{
			_SkeletalMesh->PlayAnimation(_CowerAnimation, loop);
		}
		break;
	}
	case EAnimationType::PhoneCall:
	{
		if (_PhoneCallAnimation)
		{
			_SkeletalMesh->PlayAnimation(_PhoneCallAnimation, loop);
		}
		break;
	}
	}
}

float APedestrian::GetAnimationLength(EAnimationType animationType)
{
	switch (animationType)
	{
	case EAnimationType::Idle:
	{
		if (_IdleAnimation)
		{
			return _IdleAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::Walking:
	{
		if (_WalkingAnimation)
		{
			return _WalkingAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::Running:
	{
		if (_RunningAnimation)
		{
			return _RunningAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::Reacting:
	{
		if (_ReactingAnimation)
		{
			return _ReactingAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::Sitting:
	{
		if (_SitAnimation)
		{
			return _SitAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::Cower:
	{
		if (_CowerAnimation)
		{
			return _CowerAnimation->GetPlayLength();
		}
		break;
	}
	case EAnimationType::PhoneCall:
	{
		if (_PhoneCallAnimation)
		{
			return _PhoneCallAnimation->GetPlayLength();
		}
		break;
	}
	}

	return 0.f;
}

