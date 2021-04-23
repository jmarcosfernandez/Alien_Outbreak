// Fill out your copyright notice in the Description page of Project Settings.


#include "PAttackHitbox.h"

// Sets default values
APAttackHitbox::APAttackHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);

	Speed = 0.f;

	RootComponent = SphereMesh;
}

// Called when the game starts or when spawned
void APAttackHitbox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APAttackHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector forward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + forward * Speed);

}

