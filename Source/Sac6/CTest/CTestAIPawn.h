// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CTestAIPawn.generated.h"

UCLASS()
class SAC6_API ACTestAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACTestAIPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mBody = nullptr;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* mMovement = nullptr;
	float					mHP = 100.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;
};
