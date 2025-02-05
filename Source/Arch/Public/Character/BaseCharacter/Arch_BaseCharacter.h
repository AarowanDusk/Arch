// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Arch_BaseCharacter.generated.h"

UCLASS()
class ARCH_API AArch_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AArch_BaseCharacter();

public:	

	virtual void Tick(float DeltaTime) override;
};
