// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Arch_PlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class AArch_BaseCharacter;
class AArch_GameModeBase;

struct FInputActionValue;

UCLASS()
class ARCH_API AArch_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

private:

	AArch_BaseCharacter* CharacterReference;
	AArch_GameModeBase* GameMode;

	bool bIsFirstPerson{false};
	bool bOldBool{ true };


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction{};	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PawnAction{};	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReturnAction{};

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PawnChangeAction(const FInputActionValue& Value);
	void ReturnToPlayerStart(const FInputActionValue& Value);

	void ToggleFirstPersonView();

	FTimerHandle ToggleViewTimerHandle;
};

