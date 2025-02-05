#include "Actor/Roof/Arch_RoofActor.h"

// Sets default values
AArch_RoofActor::AArch_RoofActor()
{
    // Enable ticking if needed
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AArch_RoofActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AArch_RoofActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to show the actor
void AArch_RoofActor::ShowRoof()
{
    SetActorHiddenInGame(false);   // Make the actor visible
    SetActorEnableCollision(true); // Enable collision
}

// Function to hide the actor
void AArch_RoofActor::HideRoof()
{
    SetActorHiddenInGame(true);    // Hide the actor
    SetActorEnableCollision(false); // Disable collision to prevent interactions
}