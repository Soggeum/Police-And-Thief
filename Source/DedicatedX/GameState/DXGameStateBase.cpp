// DXGameStateBase.cpp


#include "GameState/DXGameStateBase.h"

#include "Net/UnrealNetwork.h"

ADXGameStateBase::ADXGameStateBase()
{
	MaxTime = 30;
	RemainingTime = MaxTime;
}

void ADXGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, AlivePlayerControllerCount);
	DOREPLIFETIME(ThisClass, MatchState);
	DOREPLIFETIME(ThisClass, RemainingTime);
}
