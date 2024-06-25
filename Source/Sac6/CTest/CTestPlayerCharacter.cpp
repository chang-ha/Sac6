// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputData.h"

// Sets default values
ACTestPlayerCharacter::ACTestPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MyArm"));
	mArm->SetupAttachment(RootComponent);
	mArm->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 0.0, 0.0));
	mArm->TargetArmLength = 500.f;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	mCamera->SetupAttachment(mArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (true == MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

// Called when the game starts or when spawned
void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// GetController()->IsPlayerController();
	// Cast ~= dynamic_cast
	// Judge CurController is PlayerController
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		// Get EnhancedInputLocalPlayerSubsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// Get CDO
		const UTestInputData* InputData = GetDefault<UTestInputData>();
		// 1. Context == InputData's DefaultContext
		// 2. Priority == 0
		Subsystem->AddMappingContext(InputData->mDefaultContext, 0);
	}
}

// Called every frame
void ACTestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTestPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		const UTestInputData* InputData = GetDefault<UTestInputData>();
		// 1. IA's Asset
		// 2. Trigger
		// 3. Actor Pointer
		// 4. Function Address
		EnhancedInputComponent->BindAction(
			InputData->mMove, 
			ETriggerEvent::Triggered, 
			this, 
			&ACTestPlayerCharacter::MoveAction);

		EnhancedInputComponent->BindAction(
			InputData->mRotation,
			ETriggerEvent::Triggered,
			this,
			&ACTestPlayerCharacter::RotationAction);


		EnhancedInputComponent->BindAction(
			InputData->mAttack,
			ETriggerEvent::Started,
			this,
			&ACTestPlayerCharacter::AttackAction);

		EnhancedInputComponent->BindAction(
			InputData->mShield,
			ETriggerEvent::Started,
			this,
			&ACTestPlayerCharacter::ShieldAction);
	}
}

void ACTestPlayerCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();

	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void ACTestPlayerCharacter::RotationAction(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();

	// AddOnScreenDebugMessage == ����Ʈ�� ���ϴ� ���ڿ��� ������ִ� �Լ�
	// 1. Key == -1 ������ �� << ������ ���ʿ� X
	// 2. TimeToDisplay == �� �� ȭ�鿡 �����̳�
	// 3. FColor == UE�� ����ý��� RGB(255,255,255)A(255)
	// 4. FString == ����ϰ��� �ϴ� String
	// * FString == (Unicode)UE���� ���� ���ڿ� Ŭ����
	// * Printf == ȭ�鿡 ���ڿ� ��� X / ���ڿ��� ����� �ִ� �Լ�
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("X : %f Y : %f"), Axis.X, Axis.Y));
}

void ACTestPlayerCharacter::AttackAction(const FInputActionValue& Value)
{
	
}

void ACTestPlayerCharacter::ShieldAction(const FInputActionValue& Value)
{

}