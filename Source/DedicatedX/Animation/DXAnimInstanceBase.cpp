#include "Animation/DXAnimInstanceBase.h"

#include "Character/DXCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDXAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ADXCharacter>(GetOwningActor());
	if (IsValid(OwnerCharacter))
	{
		OwnerCharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UDXAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(OwnerCharacter)|| !IsValid(OwnerCharacterMovementComponent))
	{
		return;
	}

	Velocity = OwnerCharacterMovementComponent->Velocity;
	GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();
	bShouldMove = ((OwnerCharacterMovementComponent->GetCurrentAcceleration().IsNearlyZero()) == false) && (3.f < GroundSpeed);
	bIsFalling = OwnerCharacterMovementComponent->IsFalling();
	AimPitch = OwnerCharacter->GetCurrentAimPitch();
}

void UDXAnimInstanceBase::AnimNotify_CheckMeleeAttackHit()
{
	if (IsValid(OwnerCharacter) == true)
	{
		OwnerCharacter->CheckMeleeAttackHit();
	}
}