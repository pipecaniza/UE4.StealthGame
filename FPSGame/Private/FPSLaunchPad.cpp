// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(50.0f));

	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -140.0f));
	StaticMeshComp->SetupAttachment(RootComponent);

	ArrowStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowStaticMeshComp"));
	ArrowStaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 105.0f));
	ArrowStaticMeshComp->SetupAttachment(StaticMeshComp);
}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX, GetActorLocation());

	if (OtherActor)
	{
		FVector Forward = GetActorForwardVector();
		Forward.SetComponentForAxis(EAxis::Z, 1.0f);

		AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
		if (Player)
		{			
			Player->LaunchCharacter(Forward * LaunchPadVelocity, false, false);
		}
		else if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(Forward * LaunchPadVelocity * OtherComp->GetMass());
		}
	}
}
