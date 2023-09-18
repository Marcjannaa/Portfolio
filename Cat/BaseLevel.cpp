// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevel.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


template<typename ComponentType>
ComponentType* GetComponentByName(AActor* Actor, const FName& ComponentName)
{
	check(Actor);

	// get all components of given actor
	TArray<UActorComponent*> ComponentsArray;
	Actor->GetComponents(ComponentsArray);

	// find the component
	for (UActorComponent* Component : ComponentsArray)
	{
		// check the type and the 
		
		if (Component && Component->IsA<ComponentType>() && Component->GetName().Equals(*ComponentName.ToString(), ESearchCase::CaseSensitive))
		{
			// casting the component to this class
			return Cast<ComponentType>(Component);
		}
	}

	return nullptr; // <- when the component is not found
}

// Sets default values
ABaseLevel::ABaseLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Box"));
	
	const FVector NewLocation(1410.0f, 0.0f, 0.0f);
	StaticMesh->SetRelativeLocation(NewLocation);*/
}

// Called when the game starts or when spawned
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();
	if (Trigger != nullptr)
	{
		Trigger->bHiddenInGame = true;
	}
	
	UBoxComponent* TriggerBox = GetComponentByName<UBoxComponent>(this ,TEXT("Trigger Box"));
	UBoxComponent* SpawnLocationBox = GetComponentByName<UBoxComponent>(this ,TEXT("Spawn Location Box"));
	if (SpawnLocationBox)
	{
		SpawnLocation = SpawnLocationBox; 
	}
	if(TriggerBox)
	{
		Trigger = TriggerBox;
	}
	
}

// Called every frame
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBoxComponent* ABaseLevel::GetTrigger()
{
	return Trigger;
} 

UBoxComponent* ABaseLevel::GetSpawnLocation()
{
	return SpawnLocation;
}
