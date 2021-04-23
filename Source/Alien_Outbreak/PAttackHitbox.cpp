// Fill out your copyright notice in the Description page of Project Settings.


#include "PAttackHitbox.h"
#include "Alien_BreakOutBossOne.h"
#include "Alien_OutbreakCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APAttackHitbox::APAttackHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->SetCollisionProfileName(TEXT("OverlapAll"));


	Speed = 10.f;

	RootComponent = SphereMesh;
}

// Called when the game starts or when spawned
void APAttackHitbox::BeginPlay()
{
	Super::BeginPlay();

	SphereMesh->OnComponentBeginOverlap.AddDynamic(this, &APAttackHitbox::OnOverlapBegin);
	forward = GetActorForwardVector();
	SphereMesh->OnComponentBeginOverlap.AddDynamic(this, &APAttackHitbox::OnOverlapBegin);

}

// Called every frame
void APAttackHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector forward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + forward * Speed);
	
	//UE_LOG(LogTemp, Warning, TEXT("forward: %f %f %f!"), forward.X, forward.Y, forward.Z);
	if (forward.Y > 0)
		SetActorLocation(GetActorLocation() + FVector(0.0, 1.0, 0.0) * Speed);
	else
		SetActorLocation(GetActorLocation() + FVector(0.0, -1.0, 0.0) * Speed);
}


void APAttackHitbox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AAlien_BreakOutBossOne::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Player hit boss!"));

		((AAlien_BreakOutBossOne*)OtherActor)->hitByPlayer(0.03f);
		this->Destroy();
	}

}


