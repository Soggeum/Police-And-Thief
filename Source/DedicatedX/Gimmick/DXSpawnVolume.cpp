// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/DXSpawnVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ADXSpawnVolume::ADXSpawnVolume() : 
	SpawnCount(15)
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	SpawnActorClass = nullptr;
}

void ADXSpawnVolume::BeginPlay()
{
	if (HasAuthority() == false)
		return;

	for (int i = 0; i < SpawnCount; i++) {
		SpawnItem();
	}
}

FVector ADXSpawnVolume::GetRandomPointVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

FRotator ADXSpawnVolume::GetRandomRotator()
{
	float RandomYaw = FMath::FRandRange(-180.0f, 180.0f);
	return FRotator(0.f, RandomYaw, 0.f);
}

AActor* ADXSpawnVolume::SpawnItem()
{
	if (!SpawnActorClass) return nullptr;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		SpawnActorClass,
		GetRandomPointVolume(),
		GetRandomRotator()
	);

	return SpawnedActor;
}

