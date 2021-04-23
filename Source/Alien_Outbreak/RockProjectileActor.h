// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RockProjectileActor.generated.h"

UCLASS()
class ALIEN_OUTBREAK_API ARockProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	float angleAxis;
	FVector dimention;
	FVector axis;
	float rotateSpeed;
	void rotating(float DeltaTime);

	int timeTick;
	float waitTime;
	bool readyToFire;
	bool firing;
	FVector direction;

	float fireSpeed;
	void readyFire();
	void fireAtPlayer();

	FVector readyLoc;
	FVector readyDirection;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
