// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestBullet.h"

// Sets default values
ACTestBullet::ACTestBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);
	mMovement->SetUpdatedComponent(mBody);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Sphere.Sphere'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	mBody->SetSphereRadius(50.f);
	mMovement->InitialSpeed = 1500.f;
	mMovement->bShouldBounce = false;

	mBody->SetCollisionProfileName(TEXT("PlayerAttack"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ACTestBullet::BeginPlay()
{
	Super::BeginPlay();

	mMovement->OnProjectileStop.AddDynamic(this, &ACTestBullet::ProjectileHit);
}

// Called every frame
void ACTestBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTestBullet::ProjectileHit(const FHitResult& _HitResult)
{
	// UParticleSystem : 캐스케이드 파티클 시스템 에셋 타입
	// 1. LoadObject : 참조없는 에셋을 로딩하고 참조할 떄 사용
	//	1) Outer : 이녀석을 소유하고 있는 녀석
	//	2) Name : 경로
	UParticleSystem* Particle = LoadObject<UParticleSystem>(
		GetWorld(), 
		TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/P_Marketing_WeaponSwitch_02.P_Marketing_WeaponSwitch_02'")
	);

	// 1.FindObject : 참조 있는 에셋을 참조할 때 사용
	//	1) Outer : 이녀석을 소유하고 있는 녀석
	//	2) Name : 경로
	//	FindObject<UParticleSystem>(
	//		GetWorld(),
	//		TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/P_Marketing_WeaponSwitch_02.P_Marketing_WeaponSwitch_02'")
	//	);

	// IsValid : 유효성 체크. UObject 객체가 유효한 객체인지 판단해준다.
	//if (IsValid(Particle))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Particle"));
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("NonParticle"));
	//}

	// HitResult
	// 1. ImpactPoint : 부딪힌 위치
	// 2. ImpactNormal : 방향벡터

	// SpawnEmitterAtLocation
	// 1. 월드객체
	// 2. 소환하려는 파티클
	// 3. 위치
	// 4. 회전
	// 5. 자동으로 파괴할건지? (파티클 끝나면 자동으로 파괴함)
	if (IsValid(Particle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, _HitResult.ImpactPoint, _HitResult.ImpactNormal.Rotation(), true);
	}

	USoundBase* Sound = LoadObject<USoundBase>(GetWorld(),
		TEXT(""));

	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, /*_HitResult.ImpactNormal*/_HitResult.ImpactPoint);
	}
}
