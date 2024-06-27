// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestAIPawn.h"

// Sets default values
ACTestAIPawn::ACTestAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->SetCapsuleHalfHeight(85.f);
	mBody->SetCapsuleRadius(40.f);
	mBody->SetCollisionProfileName(TEXT("Monster"));

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mBody);
	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -85.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(mBody);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Siege_Dawn.Minion_Lane_Siege_Dawn'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ACTestAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTestAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


