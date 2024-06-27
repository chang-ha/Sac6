// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestItem.h"
#include "CTestGameMode.h"

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
	
	// Block 일때 부딪히면 발생
	// mBody->OnComponentHit

	// OverLap일때
	mBody->OnComponentBeginOverlap.AddDynamic(this, &ACTestItem::CollisionBeginOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this, &ACTestItem::CollisionEndOverlap);
}

// Called every frame
void ACTestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACTestItem::CollisionBeginOverlap(
	UPrimitiveComponent*	OverlappedComponent,
	AActor*					OtherActor,
	UPrimitiveComponent*	OtherComp,
	int32					OtherBodyIndex,
	bool					bFromSweep,
	const FHitResult&		SweepResult)
{
	UE_LOG(Sac6, Warning, TEXT("Begin Overlap"));

	// 액터 제거 함수

	ACTestGameMode* GameMode = GetWorld()->GetAuthGameMode<ACTestGameMode>();

	if (GameMode)
	{
		GameMode->AddScore(10);
	}

	Destroy();
}

void ACTestItem::CollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32					OtherBodyIndex)
{
	UE_LOG(Sac6, Warning, TEXT("End Overlap"));
}