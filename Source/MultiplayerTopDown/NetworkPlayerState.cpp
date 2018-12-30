// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkPlayerState.h"
#include "UnrealNetwork.h"

void ANetworkPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetworkPlayerState, PlayerCharacterRef);
}