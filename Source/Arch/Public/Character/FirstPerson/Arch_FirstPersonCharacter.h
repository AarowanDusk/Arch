// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter/Arch_BaseCharacter.h"
#include "Arch_FirstPersonCharacter.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class ARCH_API AArch_FirstPersonCharacter : public AArch_BaseCharacter
{
	GENERATED_BODY()
	
public:

	AArch_FirstPersonCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext{};


public:

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	UCameraComponent* CameraComponent() const { return FirstPersonCameraComponent; }
};
