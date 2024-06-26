// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestShield.h"

// Sets default values
ACTestShield::ACTestShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Cube.Cube'"));
	if (CubeMesh.Succeeded())
	{
		mMesh->SetStaticMesh(CubeMesh.Object);
	}

	mMesh->SetRelativeScale3D(FVector(0.2, 0.5, 0.5));
	SetLifeSpan(5.f);
}

// Called when the game starts or when spawned
void ACTestShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTestShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

