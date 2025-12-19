#pragma once

#include "Components/WidgetComponent.h"
#include "DXHPTextWidgetComponent.generated.h"

/**
 *
 */
UCLASS()
class DEDICATEDX_API UDXHPTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;
};