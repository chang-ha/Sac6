// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CTestBullet.generated.h"

UCLASS()
class SAC6_API ACTestBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTestBullet();

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* mBody = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* mMovement = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ProjectileHit(const FHitResult& _HitResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
