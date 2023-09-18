// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CatClass.generated.h"

UCLASS()
class CAT_API ACatClass : public ACharacter
{

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		UCameraComponent* FollowCamera;
	
	
	
public:
	// Sets default values for this character's properties
	ACatClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	
	void MoveRight(float value);
	void Dashing();
	float DashDistance = 6000;
	bool isDashing;
	
	//handles delay between dashes
	FTimerHandle DashDelayTimerHandle;

	//reset players ability to dash
	void ResetDash();
	void RestartLevel();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float zPosition;
	FVector tempPos = FVector();
	bool CanMove;

public:
	void AddWalkSpeed(float adding);

	int DeadCounter;
	int CoinCounter;
	int LevelCounter;

	bool isFalling;
	bool isRunning;
	bool isIdle;
	
	UFUNCTION()
	void AddCoin();
	void AddLevel();

	
	UFUNCTION()
	bool bGetDash(); // dash getter
	void death(); // death logic

	// setting events for paper flipbook animations :
	UFUNCTION(BlueprintImplementableEvent)
	void OnRun();

	UFUNCTION(BlueprintImplementableEvent)
	void OnJump();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIdle();
};
