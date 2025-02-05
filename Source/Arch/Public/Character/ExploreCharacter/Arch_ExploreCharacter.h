// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter/Arch_BaseCharacter.h"
#include "Arch_ExploreCharacter.generated.h"

/**
 * 
 */

class UCameraComponent;
class UInputMappingContext;

UCLASS()
class ARCH_API AArch_ExploreCharacter : public AArch_BaseCharacter
{
	GENERATED_BODY()

public:

	AArch_ExploreCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

public:

	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext{};
};
