// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "CTestItem.generated.h"

UCLASS()
class SAC6_API ACTestItem : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) UBoxComponent* mBody = nullptr;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* mMesh = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ACTestItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION() 
	void CollisionBeginOverlap(
		UPrimitiveComponent*	OverlappedComponent,
		AActor*					OtherActor,
		UPrimitiveComponent*	OtherComp,
		int32					OtherBodyIndex,
		bool					bFromSweep,
		const FHitResult&		SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(
		UPrimitiveComponent*	OverlappedComponent, 
		AActor*					OtherActor,
		UPrimitiveComponent*	OtherComp,
		int32					OtherBodyIndex);

};
