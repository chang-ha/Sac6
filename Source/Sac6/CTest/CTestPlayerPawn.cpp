// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerPawn.h"

// Sets default values
ACTestPlayerPawn::ACTestPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mMesh);
}

// Called when the game starts or when spawned
void ACTestPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTestPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTestPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

