// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

StateMachine::StateMachine()
{
	currentState = new State_Idle();

	//stateDictionary.insert({ "Idle", new State() });
}

StateMachine::~StateMachine()
{
}

void StateMachine::tick()
{
	currentState->tick();
}

void StateMachine::input()
{
	
}
