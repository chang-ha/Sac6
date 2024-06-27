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
	// UParticleSystem : ĳ�����̵� ��ƼŬ �ý��� ���� Ÿ��
	// 1. LoadObject : �������� ������ �ε��ϰ� ������ �� ���
	//	1) Outer : �̳༮�� �����ϰ� �ִ� �༮
	//	2) Name : ���
	UParticleSystem* Particle = LoadObject<UParticleSystem>(
		GetWorld(), 
		TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/P_Marketing_WeaponSwitch_02.P_Marketing_WeaponSwitch_02'")
	);

	// 1.FindObject : ���� �ִ� ������ ������ �� ���
	//	1) Outer : �̳༮�� �����ϰ� �ִ� �༮
	//	2) Name : ���
	//	FindObject<UParticleSystem>(
	//		GetWorld(),
	//		TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/P_Marketing_WeaponSwitch_02.P_Marketing_WeaponSwitch_02'")
	//	);

	// IsValid : ��ȿ�� üũ. UObject ��ü�� ��ȿ�� ��ü���� �Ǵ����ش�.
	//if (IsValid(Particle))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Particle"));
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("NonParticle"));
	//}

	// HitResult
	// 1. ImpactPoint : �ε��� ��ġ
	// 2. ImpactNormal : ���⺤��

	// SpawnEmitterAtLocation
	// 1. ���尴ü
	// 2. ��ȯ�Ϸ��� ��ƼŬ
	// 3. ��ġ
	// 4. ȸ��
	// 5. �ڵ����� �ı��Ұ���? (��ƼŬ ������ �ڵ����� �ı���)
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
