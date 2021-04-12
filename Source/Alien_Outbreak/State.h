 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ALIEN_OUTBREAK_API State
{
public:
	State();
	~State();
	virtual void tick();
	virtual void input();
};
