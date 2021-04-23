// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_BreakOutBossOne.h"

#include "Components/StaticMeshComponent.h"

#include "BossHPWidget.h"

#include "RockProjectileActor.h"




int rockLeft = 0;
ARockProjectileActor* rocks[3];

// Sets default values
AAlien_BreakOutBossOne::AAlien_BreakOutBossOne()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	timeTick = 0;
	fps = 60;
	summonCoolDown = 10;
	attackCoolDown = 3;
	teleportCoolDown = 15;

	teleportLocation.Add(FVector(0, 0, 0));
}

void AAlien_BreakOutBossOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called when the game starts or when spawned
void AAlien_BreakOutBossOne::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAlien_BreakOutBossOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (((timeTick % (summonCoolDown * fps)) == 0)) {
		SetFSMState(GameStates::SUMMON);
	}
	else if ((timeTick % (attackCoolDown * fps)) == 0 && rockLeft != 0) {
		SetFSMState(GameStates::ATTACK);
	}
	else if (((timeTick % (teleportCoolDown * fps)) == 0)) {
		//SetFSMState(GameStates::TELEPORT);
	}
	else {
		SetFSMState(GameStates::IDLE);
	}

	timeTick++;

	FSMUpdate();
}

void AAlien_BreakOutBossOne::BossHP_Setter(float new_HP) {
	HP = new_HP;
}

void AAlien_BreakOutBossOne::onAttackHit(float minsHP) {
	// Reduce boss hp on hit
	this->HP -= minsHP;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}

void AAlien_BreakOutBossOne::FSMUpdate()
{
	// List all expected states and call relevant state functions
	if (State == GameStates::IDLE)
	{
		if (Event == GameEvents::ON_ENTER) {
			Idle_Enter();
		}
		if (Event == GameEvents::ON_UPDATE) {
			Idle_Update();
		}
	}

	if (State == GameStates::SUMMON)
	{
		if (Event == GameEvents::ON_ENTER) {
			Summon_Enter();
		}
		if (Event == GameEvents::ON_UPDATE) {
			Summon_Update();
		}
	}
	if (State == GameStates::ATTACK)
	{
		if (Event == GameEvents::ON_ENTER) {
			Attack_Enter();
		}
		if (Event == GameEvents::ON_UPDATE) {
			Attack_Update();
		}
	}
	if (State == GameStates::TELEPORT)
	{
		if (Event == GameEvents::ON_ENTER) {
			Teleport_Enter();
		}
		if (Event == GameEvents::ON_UPDATE) {
			Teleport_Update();
		}
	}

	// Append any GameStates you add to this example..
}

void AAlien_BreakOutBossOne::SetFSMState(GameStates newState)
{
	// Append any GameStates you add to this example to this switch statement...
	switch (State)
	{
	case GameStates::IDLE:
		Idle_Exit();
		break;
	case GameStates::SUMMON:
		Summon_Exit();
		break;
	case GameStates::ATTACK:
		Attack_Exit();
		break;
	case GameStates::TELEPORT:
		Teleport_Exit();
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Unexpected state has not been implemented!"), newState);
		return;
	}

	// Set new GameStates state and begin OnEnter of that state
	State = newState;
	Event = GameEvents::ON_ENTER;
}

void AAlien_BreakOutBossOne::Idle_Enter()
{
	Event = GameEvents::ON_UPDATE;
}

void AAlien_BreakOutBossOne::Idle_Update()
{
}

void AAlien_BreakOutBossOne::Idle_Exit()
{
}

void AAlien_BreakOutBossOne::Summon_Enter()
{
	Event = GameEvents::ON_UPDATE;

	rockLeft = 3;

	FVector loc = GetActorLocation();

	// Prevent overlap at spawn
	loc.X += 200;
	rocks[0] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());
	loc.X += 200;
	rocks[1] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());
	loc.X += 200;
	rocks[2] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());

	rocks[0]->axis = FVector(0, 0.5, 0.5);
	rocks[0]->angleAxis = 180.f;
	rocks[0]->rotateSpeed = 140.f;
	rocks[0]->dimention = FVector(330, 0, 0);

	rocks[1]->axis = FVector(0, -0.5, 0.5);
	rocks[1]->angleAxis = 90.f;
	rocks[1]->rotateSpeed = 140.f;
	rocks[1]->dimention = FVector(240, 0, 0);

	rocks[2]->axis = FVector(0, 0, 1);
	rocks[2]->angleAxis = -90.f;
	rocks[2]->rotateSpeed = 140.f;
	rocks[2]->dimention = FVector(180, 0, 0);
}

void AAlien_BreakOutBossOne::Summon_Update()
{

}

void AAlien_BreakOutBossOne::Summon_Exit()
{
}

void AAlien_BreakOutBossOne::Attack_Enter()
{
	Event = GameEvents::ON_UPDATE;

	rocks[rockLeft - 1]->readyFire();
	//rocks[rockLeft - 1] = NULL;
}

void AAlien_BreakOutBossOne::Attack_Update()
{
}

void AAlien_BreakOutBossOne::Attack_Exit()
{
	rockLeft--;
}

void AAlien_BreakOutBossOne::Teleport_Enter()
{
	Event = GameEvents::ON_UPDATE;
}

void AAlien_BreakOutBossOne::Teleport_Update()
{
}

void AAlien_BreakOutBossOne::Teleport_Exit()
{
}

