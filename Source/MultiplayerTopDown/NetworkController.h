// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetworkPawn.h"
#include "PlayerCharacter.h"
#include "NetworkPlayerState.h"
#include "PlayerCharacterController.h"
#include "NetworkController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTOPDOWN_API ANetworkController : public APlayerController
{
	GENERATED_BODY()

public:
	ANetworkController();

	void Tick(float DeltaTime);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawnPlayer();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInitPlayer();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMoveCharacter();

	void InitPlayer();

	void CaptureMouseLocation();

	void UpdateCameraLocation(float DeltaTime);

	void OnSetDestinationPressed();

	UPROPERTY(EditAnywhere, Replicated)
	class ANetworkPawn* NetworkPawnRef;

	UPROPERTY(EditAnywhere, Replicated)
	class APlayerCharacter* PlayerCharacterRef;
	
	UPROPERTY(EditAnywhere, Replicated)
	class ANetworkPlayerState* NetworkPlayerState;

	UPROPERTY(EditAnywhere)
	class APlayerCharacterController* PlayerCharacterControllerRef;

	UPROPERTY(EditAnywhere)
	FVector MouseLocation;

	UPROPERTY(EditAnywhere)
	float MinClickDistance;

	UPROPERTY(EditAnywhere)
	float SpawnDelay;

	bool IsPlayerSpawned;
};
