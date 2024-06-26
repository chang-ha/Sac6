// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestItem.h"

// Sets default values
ACTestItem::ACTestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBody->SetCollisionProfileName(TEXT("Item"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Cube.Cube'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	mBody->SetBoxExtent(FVector(50.0, 50.0, 50.0));
}

// Called when the game starts or when spawned
void ACTestItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

