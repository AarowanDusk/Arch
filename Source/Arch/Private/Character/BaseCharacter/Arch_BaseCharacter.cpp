// CC Aarowan Vespera

#include "Character/BaseCharacter/Arch_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AArch_BaseCharacter::AArch_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 240.f;
	GetCharacterMovement()->MaxAcceleration = 400.f;
	GetCharacterMovement()->BrakingFrictionFactor = .5f;
	GetCharacterMovement()->GroundFriction = 5.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void AArch_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


