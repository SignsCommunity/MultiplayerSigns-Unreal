// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NetworkController.h"
#include "PlayerCharacter.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTOPDOWN_API APlayerCharacterController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	class APlayerCharacter* PlayerCharacterRef;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(ExposeOnSpawn="true"))
	class ANetworkController* NetworkControllerRef;
	
};
