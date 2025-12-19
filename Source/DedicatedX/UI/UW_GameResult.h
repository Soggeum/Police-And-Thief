// UW_GameResult.h

#pragma once

#include "Blueprint/UserWidget.h"
#include "UW_GameResult.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class DEDICATEDX_API UUW_GameResult : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> RankingText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> ReturnToTitleButton;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnReturnToTitleButtonClicked();
};
