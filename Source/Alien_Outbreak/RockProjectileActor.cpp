// Fill out your copyright notice in the Description page of Project Settings.


#include "RockProjectileActor.h"
#include "Kismet/GameplayStatics.h"
#include "Alien_Outbreak_BossOne.h"


// Sets default values
ARockProjectileActor::ARockProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh->SetStaticMesh(SphereMeshAsset.Object);
	Mesh->SetCollisionProfileName(TEXT("OverlapAll"));

	RootComponent = Mesh;

	fireSpeed = 10.f;
	dimention = FVector(300, 0, 0);
	axis = FVector(0, 0, 1);
	rotateSpeed = 90.f;

	timeTick = 0;
	waitTime = 0.5;
	readyToFire = false;
	firing = false;
	//direction;
}

// Called when the game starts or when spawned
void ARockProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARockProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (readyToFire) {
		timeTick++;
		if (timeTick >= waitTime * 60 && !firing) {
			FVector targetLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			FVector curLocation = GetActorLocation();
			direction = (targetLocation - curLocation);
			direction.Normalize();
			firing = true;
		}
		if (firing) {
			fireAtPlayer();
		}
	}
	else {
		rotating(DeltaTime);
	}
}

void ARockProjectileActor::rotating(float DeltaTime) {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAlien_Outbreak_BossOne::StaticClass(), FoundActors);

	FVector NewLocation = this->GetActorLocation();

	for (AActor* Actor : FoundActors)
	{
		NewLocation = Actor->GetActorLocation();
	}
	angleAxis += DeltaTime * rotateSpeed;
	
	if(angleAxis >= 360){
		angleAxis = 0;
	}

	FVector rotateValue = dimention.RotateAngleAxis(angleAxis, axis);

	NewLocation.X += rotateValue.X;
	NewLocation.Y += rotateValue.Y;
	NewLocation.Z += rotateValue.Z;

	FRotator NewRotation = FRotator(0, angleAxis, 0);
	FQuat QuatRotation = FQuat(NewRotation);
	SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);
}

void ARockProjectileActor::readyFire() {
	readyToFire = true;
}

void ARockProjectileActor::fireAtPlayer() {
	//UE_LOG(LogTemp, Error, TEXT("Firing Direction: %s"), *direction.ToString());
	SetActorLocation(GetActorLocation() + direction * fireSpeed);
	return;
}
