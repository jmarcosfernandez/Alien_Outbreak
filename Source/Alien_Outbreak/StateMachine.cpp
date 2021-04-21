// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

StateMachine::StateMachine()
{
	stateDictionary = {
		{"Idle", (new State_Idle)},
		{"Move", (new State_Move)},
		{"Dash", (new State_Dash)},
		{"Jump", (new State_Jump)},
		{"Attack", (new State_Attack)},
		{"Hurt", (new State_Hurt)},
		{"Death", (new State_Death)}
	};

	currentState = "Idle";
	getCurrentState = currentState;
	getStateDictionary = stateDictionary;
}

StateMachine::~StateMachine()
{
}

void StateMachine::setState(string newState)
{
	std::map<string, State*>::iterator nState;
	nState = stateDictionary.find(newState);
}

void StateMachine::transitionTo(string targetState, map<string, State*> dictionary)
{
	setState(targetState);
	currentState = targetState;
}