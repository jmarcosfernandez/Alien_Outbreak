// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMyGameModeBase::BeginPlay() {
    Super::BeginPlay();

    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
    if (CurrentWidget != nullptr) {
        CurrentWidget->AddToViewport();
    }
}
