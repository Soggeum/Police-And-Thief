#include "Gimmick/DXLandMine.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Net/UnrealNetwork.h"

ADXLandMine::ADXLandMine()
	: bIsExploded(false), 
	NetCullDistance(1000.f)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollision);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(GetRootComponent());
	Particle->SetAutoActivate(false);

	SetNetCullDistanceSquared(NetCullDistance * NetCullDistance);
}

void ADXLandMine::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bIsExploded);
}

void ADXLandMine::BeginPlay()
{
	Super::BeginPlay();	

	if (HasAuthority() == true)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on server.")), true, true, FLinearColor::Green, 5.f);
	}
	else
	{
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (IsValid(OwnerPawn) == true)
		{
			if (OwnerPawn->IsLocallyControlled() == true)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on owning client.")), true, true, FLinearColor::Green, 5.f);
			}
			else
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on other client.")), true, true, FLinearColor::Green, 5.f);
			}
		}
	}

	if (OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap) == false)
	{
		OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnLandMineBeginOverlap);
	}
}

void ADXLandMine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ADXLandMine::EndPlay()")), true, true, FLinearColor::Green, 5.f);

	if (OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap))
	{
		OnActorBeginOverlap.RemoveDynamic(this, &ThisClass::OnLandMineBeginOverlap);
	}
}

void ADXLandMine::OnLandMineBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (bIsExploded)
		return;

	if (HasAuthority())
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on server.")), true, true, FLinearColor::Green, 5.f);

		MulticastRPCSpawnEffect();
		bIsExploded = true;
	}
	else
	{
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (IsValid(OwnerPawn) == true)
		{
			if (OwnerPawn->IsLocallyControlled() == true)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on owning client.")), true, true, FLinearColor::Green, 5.f);
			}
			else
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Run on other client.")), true, true, FLinearColor::Green, 5.f);
			}
		}
	}
}

void ADXLandMine::MulticastRPCSpawnEffect_Implementation()
{
	if (HasAuthority())
	{
		return;
	}

	Particle->Activate(true);
}

void ADXLandMine::OnRep_IsExploded()
{
	if (bIsExploded && IsValid(ExplodedMaterial) == true)
	{
		Mesh->SetMaterial(0, ExplodedMaterial);
	}
}
