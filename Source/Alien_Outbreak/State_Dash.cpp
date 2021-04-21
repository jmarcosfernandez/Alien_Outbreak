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
}

void State_Dash::input()
{
}

void State_Dash::enter()
{
	//Only during jump state, will interrupt the jump and use it's own momentum instead of the jumps
	//gravity doesn't effect it
	//No other inputs, you commit to the dash
}

void State_Dash::exit()
{
	//gravity returns to the player
	//keeps momementum from the dash
}