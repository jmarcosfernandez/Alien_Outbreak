// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Death.h"

State_Death::State_Death()
{
}

State_Death::~State_Death()
{
}

void State_Death::tick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Death"));
}

void State_Death::input()
{

}