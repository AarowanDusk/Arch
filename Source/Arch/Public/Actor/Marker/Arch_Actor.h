// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arch_Actor.generated.h"

class UWidgetComponent;
class AArch_RoofActor;

UCLASS()
class ARCH_API AArch_Actor : public AActor
{
	GENERATED_BODY()
	
public:	

	AArch_Actor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roof")
	TSubclassOf<AArch_RoofActor> RoofBPClass;

protected:

	virtual void BeginPlay() override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

private:
	UFUNCTION(BlueprintCallable, Category = "Roof")
	void SpawnRoof();
};
