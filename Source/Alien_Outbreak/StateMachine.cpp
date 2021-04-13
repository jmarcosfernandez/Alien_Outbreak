// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

StateMachine::StateMachine()
{
	stateDictionary["Idle"] = (new State);
	stateDictionary["Move"] = (new State);
	stateDictionary["Dash"] = (new State);
	stateDictionary["Jump"] = (new State);
	stateDictionary["Attack"] = (new State);
	stateDictionary["Hurt"] = (new State);
	stateDictionary["Death"] = (new State);

}

StateMachine::~StateMachine()
{
}


