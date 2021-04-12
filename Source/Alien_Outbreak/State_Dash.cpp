// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Dash.h"

State_Dash::State_Dash()
{
}

State_Dash::~State_Dash()
{
}

void State_Dash::tick() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Dash"));
}

void State_Dash::input() 
{

}