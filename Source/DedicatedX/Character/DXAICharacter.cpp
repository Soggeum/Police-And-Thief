// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DXAICharacter.h"
#include "Controller/DXAIController.h"
#include "GameState/DXGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADXAICharacter::ADXAICharacter()
{
	AIControllerClass = ADXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ADXAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("[Sparta] AI character has been spawned."));
}

float ADXAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ADXGameStateBase* DXGameState = Cast<ADXGameStateBase>(UGameplayStatics::GetGameState(this));
	if (IsValid(DXGameState) && DXGameState->MatchState == EMatchState::Playing)
	{
		Destroy();
	}
	return ActualDamage;
}
