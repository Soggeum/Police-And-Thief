// DXGameStateBase.h

#pragma once

#include "GameFramework/GameStateBase.h"
#include "DXGameStateBase.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	None,
	Waiting,
	Playing,
	Ending,
	End
};

/**
 *
 */
UCLASS()
class DEDICATEDX_API ADXGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADXGameStateBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 AlivePlayerControllerCount = 0;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	EMatchState MatchState = EMatchState::Waiting;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 RemainingTime;

	UFUNCTION(BlueprintPure)
	int32 GetRemainingTime() const { return RemainingTime; }

	int32 MaxTime;

	UFUNCTION(BlueprintPure)
	int32 GetMaxTime() const { return MaxTime; }
};
