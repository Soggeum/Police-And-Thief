// UW_GameResult.cpp


#include "UW_GameResult.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUW_GameResult::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnToTitleButton.Get()->OnClicked.IsAlreadyBound(this, &ThisClass::OnReturnToTitleButtonClicked) == false)
	{
		ReturnToTitleButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnReturnToTitleButtonClicked);
	}
}

void UUW_GameResult::OnReturnToTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Title")), true);
}
