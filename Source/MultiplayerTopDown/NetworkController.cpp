// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkController.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Engine/EngineTypes.h"
#include "NetworkPlayerStart.h"
#include "Kismet/GameplayStatics.h"

// Set property defaults here
ANetworkController::ANetworkController()
{
	bReplicates = true;
	SpawnDelay = 0.2;
	IsPlayerSpawned = false;
}

void ANetworkController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetworkController, NetworkPawnRef);
	DOREPLIFETIME(ANetworkController, PlayerCharacterRef);
	DOREPLIFETIME(ANetworkController, NetworkPlayerState);
}

template<typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

bool ANetworkController::ServerSpawnPlayer_Validate()
{
	return true;
}

void ANetworkController::ServerSpawnPlayer_Implementation()
{
	if (!HasAuthority() || IsPlayerSpawned) return;
	IsPlayerSpawned = true;
	TArray<ANetworkPlayerStart*> PlayerStarts;
	FindAllActors(GetWorld(), PlayerStarts);
	if (PlayerStarts.Num() < 1) return; // TODO - proper error handling 
	ANetworkPlayerStart* PS = PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];
	NetworkPawnRef->SetActorLocation(PS->GetActorLocation(), false, nullptr, TeleportFlagToEnum(true));
	FTransform NetworkPawnTransform = NetworkPawnRef->GetActorTransform();
	//auto NewPlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(APlayerCharacter::StaticClass(), NetworkPawnTransform);
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Character(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/TopDownCharacter.TopDownCharacter'"));
	if (auto NewPlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>((UClass*)BP_Character.Object->GeneratedClass, NetworkPawnTransform))
	{
		UE_LOG(LogTemp, Error, TEXT("SPAWNED PlayerCharacter"));
	}
	auto NewPlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>((UClass*)BP_Character.Object->GeneratedClass, NetworkPawnTransform);
	PlayerCharacterRef = NewPlayerCharacter;
	if (ANetworkPlayerState* NPS = Cast<ANetworkPlayerState>(PlayerState))
	{
		NPS->PlayerCharacterRef = NewPlayerCharacter;
	}
	auto NewPlayerCharacterController = GetWorld()->SpawnActorDeferred<APlayerCharacterController>(APlayerCharacterController::StaticClass(), NetworkPawnTransform);
	if (NewPlayerCharacterController)
	{
		NewPlayerCharacterController->NetworkControllerRef = this;
		UGameplayStatics::FinishSpawningActor(NewPlayerCharacterController, NetworkPawnTransform);
	}
	PlayerCharacterControllerRef = NewPlayerCharacterController;
	PlayerCharacterControllerRef->PlayerCharacterRef = PlayerCharacterRef;
	PlayerCharacterControllerRef->Possess(PlayerCharacterRef);
}

bool ANetworkController::ServerInitPlayer_Validate()
{
	return true;
}

void ANetworkController::ServerInitPlayer_Implementation()
{
	if (ANetworkPawn* NP = Cast<ANetworkPawn>(GetPawn())) {
		NetworkPawnRef = NP;
		NetworkPawnRef->NetworkControllerRef = this;
	}
}

bool ANetworkController::ServerMoveCharacter_Validate()
{
	return true;
}

void ANetworkController::ServerMoveCharacter_Implementation()
{
	if (!HasAuthority()) return;
	if ((PlayerCharacterRef->GetActorLocation() - MouseLocation).Size() < MinClickDistance) return; // TODO - could move this to _Validate() ?
	if (IsValid(PlayerCharacterControllerRef)) PlayerCharacterControllerRef->MoveToLocation(MouseLocation);
}

void ANetworkController::InitPlayer()
{
	bShowMouseCursor = true;
	ServerInitPlayer();
}

void ANetworkController::CaptureMouseLocation()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), true, HitResult);
	if (HitResult.bBlockingHit)
	{
		MouseLocation = HitResult.Location;
	}
}

void ANetworkController::UpdateCameraLocation(float DeltaTime)
{
	if (!IsValid(PlayerCharacterRef)) return;
	FVector NewLocation = FMath::VInterpTo(NetworkPawnRef->GetActorLocation(), PlayerCharacterRef->GetActorLocation(), DeltaTime, 10.0f);
	NetworkPawnRef->SetActorLocation(NewLocation);
}

// Called every frame
void ANetworkController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CaptureMouseLocation();
	UpdateCameraLocation(DeltaTime);
}

void ANetworkController::BeginPlay()
{
	FTimerHandle SpawnDelayHandle;
	GetWorldTimerManager().SetTimer(SpawnDelayHandle, this, &ANetworkController::InitPlayer, SpawnDelay, false);
}

void ANetworkController::OnSetDestinationPressed()
{
	ServerMoveCharacter();
}

void ANetworkController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ANetworkController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ANetworkController::OnSetDestinationReleased);

	//InputComponent->BindAction("Fire", IE_Pressed, this, &ANetworkController::SignFireInput);
}
