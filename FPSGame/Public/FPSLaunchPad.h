// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ArrowStaticMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* OverlapComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* ParticleFX;

	UPROPERTY(EditDefaultsOnly, Category = "Variables")
	float LaunchPadVelocity;
	
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
