// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Coins.generated.h"
class ACatClass;

UCLASS()

class CAT_API ACoins : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACoins();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
		class USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
		class UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
		class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
		class URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
		class USoundBase* OverlapSounds;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
