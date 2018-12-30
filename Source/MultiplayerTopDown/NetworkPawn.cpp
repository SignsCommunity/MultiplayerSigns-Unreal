// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ANetworkPawn::ANetworkPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, -40.0f, 0.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bEnableCameraLag = true;
	//CameraBoom->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ANetworkPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

