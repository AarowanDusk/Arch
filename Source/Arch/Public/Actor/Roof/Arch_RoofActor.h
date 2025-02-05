// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arch_RoofActor.generated.h"

UCLASS()
class ARCH_API AArch_RoofActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AArch_RoofActor();

    // Function to show the actor
    UFUNCTION(BlueprintCallable, Category = "Roof")
    void ShowRoof();

    // Function to hide the actor
    UFUNCTION(BlueprintCallable, Category = "Roof")
    void HideRoof();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
