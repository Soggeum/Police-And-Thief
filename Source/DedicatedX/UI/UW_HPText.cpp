#include "UI/UW_HPText.h"

#include "Component/DXStatusComponent.h"
#include "Components/TextBlock.h"
#include "Character/DXCharacter.h"

UUW_HPText::UUW_HPText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUW_HPText::NativeConstruct()
{
	Super::NativeConstruct();

	ADXCharacter* OwningCharacter = Cast<ADXCharacter>(OwningActor);
	if (IsValid(OwningCharacter))
	{
		OwningCharacter->SetHPTextWidget(this);
	}
}

void UUW_HPText::InitializeHPTextWidget(UDXStatusComponent* InStatusComponent)
{
	OnMaxHPChange(InStatusComponent->GetMaxHP());
	OnCurrentHPChange(InStatusComponent->GetCurrentHP());
}

void UUW_HPText::OnMaxHPChange(float InMaxHP)
{
	MaxHPText->SetText(FText::FromString(FString::SanitizeFloat(InMaxHP)));
}

void UUW_HPText::OnCurrentHPChange(float InCurrentHP)
{
	CurrentHPText->SetText(FText::FromString(FString::SanitizeFloat(InCurrentHP)));
}
