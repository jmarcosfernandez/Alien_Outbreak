// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

/**
 * 
 */
class ALIEN_OUTBREAK_API State_Death : public State
{
public:
	State_Death();
	virtual ~State_Death();
	void tick() override;
	void input() override;
	void enter() override;
	void exit() override;
};
