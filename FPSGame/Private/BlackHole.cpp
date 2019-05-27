// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	DestroySphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphereComp"));
	/*DestroySphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroySphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);*/
	DestroySphereComp->SetupAttachment(MeshComp);

	AttractSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphereComp"));
	AttractSphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> AttractOverlappedComponents;
	AttractSphereComp->GetOverlappingComponents(AttractOverlappedComponents);
	
	for (auto& Component : AttractOverlappedComponents)
	{		
		Component->AddRadialForce(GetActorLocation(), AttractSphereComp->GetScaledSphereRadius(), Strength, RIF_Constant);
	}

	TArray<AActor*> DestroyOverlappedActors;
	DestroySphereComp->GetOverlappingActors(DestroyOverlappedActors);

	for (auto& Actor : DestroyOverlappedActors)
	{
		if (Actor != this)
		{
			Actor->Destroy();
		}
	}
}

