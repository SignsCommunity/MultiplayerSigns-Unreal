// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NetworkController.h"
#include "NetworkPawn.generated.h"

UCLASS()
class MULTIPLAYERTOPDOWN_API ANetworkPawn : public APawn
{
	GENERATED_BODY()

public:
	//UPROPERTY()
	class ANetworkController* NetworkControllerRef;

	// Sets default values for this pawn's properties
	ANetworkPawn();

protected:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBoom;
	class UCameraComponent* Camera;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
