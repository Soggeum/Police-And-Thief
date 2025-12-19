#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DXLandMine.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UMaterial;

UCLASS()
class DEDICATEDX_API ADXLandMine : public AActor
{
	GENERATED_BODY()

public:
	ADXLandMine();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
	void OnLandMineBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCSpawnEffect();

	UFUNCTION()
	void OnRep_IsExploded();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UParticleSystemComponent> Particle;

	UPROPERTY(ReplicatedUsing = OnRep_IsExploded)
	uint8 bIsExploded : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float NetCullDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UMaterial> ExplodedMaterial;
};
