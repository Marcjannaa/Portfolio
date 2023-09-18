// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

#include "Components/WidgetComponent.h"

AInGameHUD::AInGameHUD()
{
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
}

