// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Move.h"

State_Move::State_Move()
{
}

State_Move::~State_Move()
{
}

void State_Move::tick() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test Move"));
}
void State_Move::input() 
{	

}
