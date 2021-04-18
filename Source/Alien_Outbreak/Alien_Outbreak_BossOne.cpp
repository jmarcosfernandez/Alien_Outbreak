// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_Outbreak_BossOne.h"

#include "Components/StaticMeshComponent.h"

#include "RockProjectileActor.h"

int timeTick = 0;
int fps = 60;
int summonCoolDown = 10;
int attackCoolDown = 3;


int rockLeft = 0;
ARockProjectileActor* rocks[3];

// Sets default values
AAlien_Outbreak_BossOne::AAlien_Outbreak_BossOne()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
}

// Called when the game starts or when spawned
void AAlien_Outbreak_BossOne::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlien_Outbreak_BossOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (((timeTick % (summonCoolDown * fps)) == 0)) {
		SetFSMState(GameStates::SUMMON);
	}
	else if ((timeTick % (attackCoolDown * fps)) == 0 && rockLeft != 0) {
		SetFSMState(GameStates::ATTACK);
	}
	else {
		SetFSMState(GameStates::IDLE);
	}

	timeTick++;

	FSMUpdate();
}

//#include "BossStateMachine.h"




void AAlien_Outbreak_BossOne::FSMUpdate()
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

void AAlien_Outbreak_BossOne::SetFSMState(GameStates newState)
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

void AAlien_Outbreak_BossOne::Idle_Enter()
{
	Event = GameEvents::ON_UPDATE;
}

void AAlien_Outbreak_BossOne::Idle_Update()
{
}

void AAlien_Outbreak_BossOne::Idle_Exit()
{
}

void AAlien_Outbreak_BossOne::Summon_Enter()
{
	Event = GameEvents::ON_UPDATE;

	rockLeft = 3;
	
	FVector loc = GetActorLocation();

	rocks[0] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());
	rocks[1] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());
	rocks[2] = GetWorld()->SpawnActor<ARockProjectileActor>(loc, GetActorRotation());

	rocks[0]->axis = FVector(0, 0.5, 0.5);
	rocks[0]->angleAxis = 180.f;
	rocks[0]->rotateSpeed = 170.f;
	rocks[0]->dimention = FVector(330, 0, 0);

	rocks[1]->axis = FVector(0, -0.5, 0.5);
	rocks[1]->angleAxis = 90.f;
	rocks[1]->rotateSpeed = 150.f;
	rocks[1]->dimention = FVector(240, 0, 0);

	rocks[2]->axis = FVector(0, 0, 1);
	rocks[2]->angleAxis = -90.f;
	rocks[2]->rotateSpeed = 140.f;
	rocks[2]->dimention = FVector(150, 0, 0);
}

void AAlien_Outbreak_BossOne::Summon_Update()
{

}

void AAlien_Outbreak_BossOne::Summon_Exit()
{
}

void AAlien_Outbreak_BossOne::Attack_Enter()
{
	Event = GameEvents::ON_UPDATE;

	rocks[rockLeft - 1]->readyFire();
	//rocks[rockLeft - 1] = NULL;
}

void AAlien_Outbreak_BossOne::Attack_Update()
{
}

void AAlien_Outbreak_BossOne::Attack_Exit()
{
	rockLeft--;
}

void AAlien_Outbreak_BossOne::Teleport_Enter()
{
	Event = GameEvents::ON_UPDATE;
}

void AAlien_Outbreak_BossOne::Teleport_Update()
{
}

void AAlien_Outbreak_BossOne::Teleport_Exit()
{
}

