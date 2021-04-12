// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

/**
 * 
 */
class ALIEN_OUTBREAK_API State_Idle : public State
{
public:
	State_Idle();
	~State_Idle();
	void tick() override;
	void input() override;
};
