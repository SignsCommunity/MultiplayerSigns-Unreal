// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacter.h"
#include "NetworkPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTOPDOWN_API ANetworkPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Replicated)
	APlayerCharacter* PlayerCharacterRef;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

};
