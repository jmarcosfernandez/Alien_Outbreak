// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

State::State()
{
	 
}


State::~State()
{
}


void State::tick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test State"));
}

void State::input()
{
}