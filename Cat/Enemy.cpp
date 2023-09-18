// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "CatClass.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;	

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(RootScene);
	CapsuleComponent->InitCapsuleSize(45.f, 45.f);
	CapsuleComponent->SetRelativeLocation(FVector(0.f,0.f,6.f));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CatClass = Cast<ACatClass>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RandomChar = FMath::RandRange(1,3);
	switch (RandomChar)
	{
	case 1: OnMushroom();
		break;
	case 2: OnEye();
		break;
	case 3: OnSkeleton();
		break;
	default: OnMushroom();
		break;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CatClass = Cast<ACatClass>(OtherActor);
	if(CatClass)
	{
		UE_LOG(LogTemp, Warning,TEXT("works"));
		if(CatClass->bGetDash())
		{
			Destroy();
		}
	}
}

