// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "StateMachine.h"

#include "GameFramework/Character.h"
#include "Alien_OutbreakCharacter.generated.h"


UCLASS(config=Game)
class AAlien_OutbreakCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AAlien_OutbreakCharacter();
	void PlayerHP_Setter(float new_HP);
	void onRockHit(float minsHP, float rockY);
	void knockBack();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool knockToLeft;
	bool knockingBack;
	float knockBackTime;
	float knockBackSpeed;
	int fps;
	int knockBackCount;

public:
		UPROPERTY(BlueprintReadOnly)
			float HP = 1.0f;
		UPROPERTY(EditAnywhere)
			TSubclassOf<class UPlayerHPWidget> WidgetClass;

private:
	enum GameStates { IDLE, MOVE, JUMP, DASH, ATTACK, HURT, DEATH };
	GameStates State = GameStates::IDLE;

	enum GameEvents { ON_ENTER, ON_UPDATE };
	GameEvents Event = GameEvents::ON_ENTER;

	void FSMUpdate();
	void SetFSMState(GameStates newState);

	void Idle_Enter();
	void Idle_Update();
	void Idle_Exit();

	void Move_Enter();
	void Move_Update();
	void Move_Exit();

	void Jump_Enter();
	void Jump_Update();
	void Jump_Exit();

	void Dash_Enter();
	void Dash_Update();
	void Dash_Exit();

	void Attack_Enter();
	void Attack_Update();
	void Attack_Exit();

	void Hurt_Enter();
	void Hurt_Update();
	void Hurt_Exit();

	void Death_Enter();
	void Death_Update();
	void Death_Exit();
};

