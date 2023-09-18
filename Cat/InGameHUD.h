// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CAT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	AInGameHUD();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		UWidgetComponent* Widget;
};
