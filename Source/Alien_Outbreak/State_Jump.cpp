// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Jump.h"


State_Jump::State_Jump()
{
}

State_Jump::~State_Jump()
{
}

void State_Jump::tick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Jump"));
}

void State_Jump::input()
{
	
}