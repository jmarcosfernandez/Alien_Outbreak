// Copyright Epic Games, Inc. All Rights Reserved.

#include "Alien_OutbreakCharacter.h"
#include "StateMachine.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerHPWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


AAlien_OutbreakCharacter::AAlien_OutbreakCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Setting up Knock Back Variables
	knockToLeft = true;
	knockingBack = false;
	knockBackTime = 0.2;
	knockBackSpeed = 20.f;
	knockBackCount = knockBackTime;
	fps = 60;

	// Loading Hurt Sounds
	static ConstructorHelpers::FObjectFinder<USoundWave> Hurt1(TEXT("SoundWave'/Game/Sounds/Hurt1'"));
	HurtSound1 = Hurt1.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> Hurt2(TEXT("SoundWave'/Game/Sounds/Hurt2'"));
	HurtSound2 = Hurt2.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> Hurt3(TEXT("SoundWave'/Game/Sounds/Hurt3'"));
	HurtSound3 = Hurt3.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> Hurt4(TEXT("SoundWave'/Game/Sounds/Hurt4'"));
	HurtSound4 = Hurt4.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> Hurt5(TEXT("SoundWave'/Game/Sounds/Hurt5'"));
	HurtSound5 = Hurt5.Object;
	
}

void AAlien_OutbreakCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto Widget = CreateWidget<UPlayerHPWidget>(UGameplayStatics::GetPlayerController(this, 0), WidgetClass);
	Widget->Player = this;
	Widget->AddToViewport();
}

void AAlien_OutbreakCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (knockingBack) {
		if(knockToLeft)
			SetActorLocation(GetActorLocation() + FVector(0, 1, 0) * knockBackSpeed);
		else
			SetActorLocation(GetActorLocation() + FVector(0, -1, 0) * knockBackSpeed);
		knockBackCount--;
		if (knockBackCount <= 0)
			knockingBack = false;
	}
	//HP -= 0.0001f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAlien_OutbreakCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAlien_OutbreakCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAlien_OutbreakCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AAlien_OutbreakCharacter::TouchStopped);
}

void AAlien_OutbreakCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AAlien_OutbreakCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AAlien_OutbreakCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AAlien_OutbreakCharacter::PlayerHP_Setter(float new_HP) {
	HP = new_HP;
}

void AAlien_OutbreakCharacter::onRockHit(float minsHP, float rockY) {
	// Reduce player hp on hit
	this->HP -= minsHP;
	if (HP <= 0.f) {
		// Player Death
	}
	
	// Playe hurt sound
	playHurtSound(FMath::RandRange(1, 5));

	// Set up knockback
	float Y = this->GetActorLocation().Y;
	if (Y > rockY)
		knockToLeft = true;
	else
		knockToLeft = false;
	knockingBack = true;
	knockBackCount = knockBackTime * fps;
}

void AAlien_OutbreakCharacter::playHurtSound(int num) {
	// Random Play hurt sound
	switch (num) {
	case 1: UGameplayStatics::PlaySound2D(this, HurtSound1); break;
	case 2: UGameplayStatics::PlaySound2D(this, HurtSound2); break;
	case 3: UGameplayStatics::PlaySound2D(this, HurtSound3); break;
	case 4: UGameplayStatics::PlaySound2D(this, HurtSound4); break;
	case 5: UGameplayStatics::PlaySound2D(this, HurtSound5); break;
	default: UGameplayStatics::PlaySound2D(this, HurtSound1); break;
	}
}