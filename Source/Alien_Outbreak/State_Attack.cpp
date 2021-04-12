// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Attack.h"

State_Attack::State_Attack()
{
}

State_Attack::~State_Attack()
{
}

void State_Attack::tick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Attack"));
}

void State_Attack::input()
{

}