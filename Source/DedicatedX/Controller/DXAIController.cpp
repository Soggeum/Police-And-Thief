// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DXAIController.h"
#include "TimerManager.h"
#include "NavigationSystem.h"

ADXAIController::ADXAIController()
{

}

void ADXAIController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			RandomMoveTimer,
			this,
			&ADXAIController::MoveToRandomLocation,
			FMath::FRandRange(3.f, 5.f),
			true,
			1.0f
		);
	}
}

void ADXAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("[Sparta] AI Controller is controlling %s."), *InPawn->GetName());
	}
}

void ADXAIController::MoveToRandomLocation()
{
	APawn* MyPawn = GetPawn();
	if (!IsValid(MyPawn))
	{
		//UE_LOG(LogTemp, Error, TEXT("[Sparta] No Pawn to control."));
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(NavSystem))
	{
		//UE_LOG(LogTemp, Error, TEXT("[Sparta] Could not find Navigation System."));
		return;
	}

	FNavLocation RandomLocation;
	bool bFoundLocation = NavSystem->GetRandomReachablePointInRadius(
		MyPawn->GetActorLocation(),
		MoveRadius,
		RandomLocation
	);

	if (bFoundLocation)
	{
		MoveToLocation(RandomLocation.Location);

		//UE_LOG(LogTemp, Warning, TEXT("[Sparta] Move target: %s"), *RandomLocation.Location.ToString());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("[Sparta] Could not find a reachable location."));
	}
}