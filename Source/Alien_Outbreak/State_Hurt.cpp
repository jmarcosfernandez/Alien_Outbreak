// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Hurt.h"

State_Hurt::State_Hurt()
{
}

State_Hurt::~State_Hurt()
{
}

void State_Hurt::tick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Hurt"));
}

void State_Hurt::input()
{

}
