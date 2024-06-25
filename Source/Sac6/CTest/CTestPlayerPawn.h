// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Camera/CameraComponent.h"
#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "CTestPlayerPawn.generated.h"

UCLASS()
class SAC6_API ACTestPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACTestPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* mMesh;
	UPROPERTY(VisibleAnywhere) UCameraComponent* mCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
