// DXBuffBox.h

#pragma once

#include "GameFramework/Actor.h"
#include "DXBuffBox.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class DEDICATEDX_API ADXBuffBox : public AActor
{
	GENERATED_BODY()

public:
	ADXBuffBox();

	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSpawnParticle();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnEffectFinished(UParticleSystemComponent* ParticleSystem);

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<UParticleSystemComponent> ParticleEffect;

};
