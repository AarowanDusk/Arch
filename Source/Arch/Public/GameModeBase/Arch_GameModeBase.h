// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Arch_GameModeBase.generated.h"

/**
 * 
 */

class AArch_ExploreCharacter;
class AArch_FirstPersonCharacter;
class UInputMappingContext;

UCLASS()
class ARCH_API AArch_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AArch_GameModeBase();

	bool bIsFirstPerson;

	void SwitchPawn();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TSubclassOf <AArch_ExploreCharacter> ExploreCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TSubclassOf <AArch_FirstPersonCharacter> FirstPersonCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext{};
};
