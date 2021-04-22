// Fill out your copyright notice in the Description page of Project Settings.


#include "RockProjectileActor.h"
#include "Kismet/GameplayStatics.h"
#include "Alien_Outbreak_BossOne.h"
#include "Alien_OutbreakCharacter.h"


// Sets default values
ARockProjectileActor::ARockProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>rockAsset(TEXT("StaticMesh'/Game/Objects/UnwrappedRock'"));
	Mesh->SetStaticMesh(rockAsset.Object);
	Mesh->SetCollisionProfileName(TEXT("OverlapAll"));

	RootComponent = Mesh;

	SetActorScale3D(GetActorScale3D() * 3.f);

	fireSpeed = 12.f;
	dimention = FVector(300, 0, 0);
	axis = FVector(0, 0, 1);
	rotateSpeed = 90.f;

	timeTick = 0;
	waitTime = 0.5;
	readyToFire = false;
	firing = false;
	//direction;
}



void ARockProjectileActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AAlien_OutbreakCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("HIT Player!"));

		float rockY = this->GetActorLocation().Y;
		// Reduce Player HP
		((AAlien_OutbreakCharacter *)GetWorld()->GetFirstPlayerController()->GetPawn())->onRockHit(0.05f, rockY);

		this->Destroy();
	}
	else if (OtherActor->IsA(AAlien_Outbreak_BossOne::StaticClass()) || OtherActor->IsA(ARockProjectileActor::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("HIT Rock or Boss!"));
		// Ignore collision with rock or boss
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HIT Wall!"));
		this->Destroy();
	}
	
	//GC
	//GetWorld()->ForceGarbageCollection(true);
}

void ARockProjectileActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor->IsA(AAlien_OutbreakCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("HIT Player!"));
		// Reduce Player HP
		this->Destroy();
	}
	else if (OtherActor->IsA(AAlien_Outbreak_BossOne::StaticClass()) || OtherActor->IsA(ARockProjectileActor::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("HIT Rock or Boss!"));
		// Ignore collision with rock or boss
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HIT Wall!"));
		this->Destroy();
	}

	//GC
	//GetWorld()->ForceGarbageCollection(true);
}

// Called when the game starts or when spawned
void ARockProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARockProjectileActor::OnOverlapBegin);
	//Mesh->OnComponentHit.AddDynamic(this, &ARockProjectileActor::OnActorHit);
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