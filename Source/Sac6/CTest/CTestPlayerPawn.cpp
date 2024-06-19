// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerPawn.h"

// Sets default values
ACTestPlayerPawn::ACTestPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(mMesh);

#if WITH_EDITORONLY_DATA
	mMesh->bVisualizeComponent = true; 
#endif

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	// Camera의 부모 Component를 mMesh로 지정한다
	mCamera->SetupAttachment(mMesh);

	// FVector
	mCamera->SetRelativeLocation(FVector(-240.0, 0.0, 90.0));
	mCamera->SetRelativeRotation(FRotator(-20.0, 0.0, 0.0));
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

