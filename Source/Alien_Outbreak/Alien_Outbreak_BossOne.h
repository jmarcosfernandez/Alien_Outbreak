// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Alien_Outbreak_BossOne.generated.h"

UCLASS()
class ALIEN_OUTBREAK_API AAlien_Outbreak_BossOne : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien_Outbreak_BossOne();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int timeTick;
	int fps;
	int summonCoolDown;
	int attackCoolDown;
	int teleportCoolDown;
	TArray<FVector> teleportLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY()
		class USceneComponent* Root;

	enum GameStates { IDLE, SUMMON, ATTACK, TELEPORT };
	GameStates State = GameStates::IDLE;

	enum GameEvents { ON_ENTER, ON_UPDATE };
	GameEvents Event = GameEvents::ON_ENTER;

	void FSMUpdate();
	void SetFSMState(GameStates newState);

	void Idle_Enter();
	void Idle_Update();
	void Idle_Exit();

	void Summon_Enter();
	void Summon_Update();
	void Summon_Exit();

	void Attack_Enter();
	void Attack_Update();
	void Attack_Exit();

	void Teleport_Enter();
	void Teleport_Update();
	void Teleport_Exit();
};
