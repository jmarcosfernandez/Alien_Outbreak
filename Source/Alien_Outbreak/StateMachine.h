// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "State.h"

#include "State_Idle.h"
#include "State_Move.h"
#include "State_Attack.h"
#include "State_Jump.h"
#include "State_Hurt.h"
#include "State_Move.h"
#include "State_Dash.h"
#include "State_Death.h"

#include <map>
#include <string>


using namespace std;

/**
 * 
 */
class ALIEN_OUTBREAK_API StateMachine
{
public:
	StateMachine();
	~StateMachine();


protected:
	State* currentState;

	map<string, State> stateDictionary;
};
