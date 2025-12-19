// DXBuffBox.cpp


#include "Gimmick/DXBuffBox.h"

#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/DXCharacter.h"
#include "GameState/DXGameStateBase.h"

ADXBuffBox::ADXBuffBox()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(TriggerBox);
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleEffect"));
	ParticleEffect->SetupAttachment(TriggerBox);
	ParticleEffect->bAutoActivate = false;
}

void ADXBuffBox::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

void ADXBuffBox::MulticastSpawnParticle_Implementation()
{
	//if (HasAuthority())
	//	return;

	//ParticleEffect->Activate(true);
	//ParticleEffect->OnSystemFinished.AddDynamic(this, &ThisClass::OnEffectFinished);
}

void ADXBuffBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!HasAuthority())
		return;

	ADXGameStateBase* GS = GetWorld()->GetGameState<ADXGameStateBase>();
	if (GS->MatchState != EMatchState::Playing)
		return;

	ADXCharacter* OverlappingCharacter = Cast<ADXCharacter>(OtherActor);
	if (IsValid(OverlappingCharacter))
	{
		if (OverlappingCharacter->ActorHasTag("Player"))
		{
			/*Mesh->SetHiddenInGame(true);
			SetActorEnableCollision(false);*/
			OverlappingCharacter->TakeBuff(50.f);
			Destroy();
		}
	}
}

void ADXBuffBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	if (HasAuthority() == true)
	{
		Destroy();
	}
}
