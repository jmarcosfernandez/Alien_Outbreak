// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAttackHitbox.generated.h"

UCLASS()
class ALIEN_OUTBREAK_API APAttackHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APAttackHitbox();
	class UStaticMeshComponent* SphereMesh;
	float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
=======
>>>>>>> parent of 044c30f (Player attack and Boss Hp reduce)
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
