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
}

void State_Hurt::input()
{
}

void State_Hurt::enter()
{
	//No actions. Will do the hurt animation and when that animation ends, will exit the state.
	//if it kills the character, will go into death state before animation
}

void State_Hurt::exit()
{
}