// Fill out your copyright notice in the Description page of Project Settings.


#include "CatClass.h"

#include "CatCharacter.h"
#include "Enemy.h"
#include "Spikes.h"
#include "WallSpike.h"
#include "Engine.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACatClass::ACatClass()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setting up some basic things visible in the character bp inherited from this class
	GetCapsuleComponent()->InitCapsuleSize(45.f, 45.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//setting up character movement logic
	GetCharacterMovement() -> bOrientRotationToMovement = true;
	GetCharacterMovement() -> RotationRate = FRotator(0.0f, 7200.0f, 0.0f);

	GetCharacterMovement() -> GravityScale = 2.0f;
	GetCharacterMovement() -> AirControl = 0.8f;
	GetCharacterMovement() -> JumpZVelocity = 800.0f;
	GetCharacterMovement() -> GroundFriction = 3.0f;
	GetCharacterMovement() -> MaxWalkSpeed = 600.0f;
	GetCharacterMovement() -> MaxFlySpeed =	600.0f;

	tempPos = GetActorLocation();
	zPosition = tempPos.Z + 300.0f;
}

// Called when the game starts or when spawned
void ACatClass::BeginPlay()
{
	Super::BeginPlay(); // BeginPlay, called on the first frame ("void start()" in Unity C#)
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACatClass::OnOverlapBegin);
	CanMove = true;
	DeadCounter = 0; 
	CoinCounter = 0;
	isDashing = false;
	OnIdle(); // bp event
}

// Called every frame
void ACatClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // tick, called every frame ("void update() in Unity C#")
	tempPos = GetActorLocation();
	tempPos.X -=850.0f;
	tempPos.Y = zPosition;
	isFalling = GetCharacterMovement()->IsFalling(); 
	if (GetCharacterMovement()->Velocity.Length() == 0)
	{
		OnIdle(); // bp event
	}
	if(isFalling)
	{
		OnJump(); // bp event
	}
}

// Called to bind functionality to input
void ACatClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//binding actions set in the UE settings :
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACatClass::Dashing);

	PlayerInputComponent->BindAxis("MoveRight", this, &ACatClass::MoveRight); 
}

void ACatClass::MoveRight(float value)
{
	OnRun(); // calling the bp event
	if(CanMove) // CanMove set to false only when player dies
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value); // adding speed to the player
	}
}

void ACatClass::Dashing()
{
	OnJump(); // calling the bp event
	if(CoinCounter>=5) // dash condition, 5 coins to dash
	{
		isDashing = true; // set to true to add the enemy logic
		CoinCounter-=5; // decrease amount of coins
		const FVector ForwardDir = this->GetActorRotation().Vector(); //get current speed
		LaunchCharacter(ForwardDir*DashDistance, true, true); //increase the speed by DashDistance
		GetWorld()->GetTimerManager().SetTimer(DashDelayTimerHandle, this, &ACatClass::ResetDash, 0.05f, false);
		// after timer ends, call ResetDash
	}
	
}

void ACatClass::ResetDash()
{
	isDashing = false;
	const FVector ForwardDir = this->GetActorRotation().Vector();
	GetWorldTimerManager().ClearTimer(DashDelayTimerHandle);
	LaunchCharacter(ForwardDir/DashDistance, true, true); // returning to the previous speed
}

void ACatClass::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void ACatClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != nullptr)
	{
		// casting obstacles/enemy classes to character class
		ASpikes* WallSpike = Cast<AWallSpike>(OtherActor);
		ASpikes* Spike = Cast<ASpikes>(OtherActor);
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if(WallSpike||Spike)
		{
			death();
		}
		if(Enemy)
		{ // if character is dashing then destroy the enemy
			if(!isDashing)
			{
				death();
			}
			else
			{
				Enemy->Destroy();
			}
		}
	}
}

void ACatClass::AddWalkSpeed(float adding)
{
	GetCharacterMovement()->MaxWalkSpeed += adding;
}

void ACatClass::AddCoin()
{
	CoinCounter++;
	UE_LOG(LogTemp, Warning,TEXT("Total coins: %d"), CoinCounter);
}

void ACatClass::AddLevel()
{
	LevelCounter++;
	UE_LOG(LogTemp, Warning,TEXT("Total levels: %d"), LevelCounter);
}

bool ACatClass::bGetDash()
{
	return isDashing;
}

void ACatClass::death()
{
	DeadCounter++;
	AddWalkSpeed(-200);
	if(DeadCounter>=3)
	{
		GetMesh()->Deactivate();
		GetMesh()->SetVisibility(false);

		CanMove = false; 
		FTimerHandle UnusedHandle; // restart level with 2 sec delay 
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACatClass::RestartLevel, 2.f, false);
	}
}