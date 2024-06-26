// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputData.h"
#include "CTestShield.h"

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
	// Trigger
	mArm->bInheritPitch = false;
	mArm->bEnableCameraLag = true;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	mCamera->SetupAttachment(mArm);

	mRotation = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldRotator"));
	mRotation->SetupAttachment(RootComponent);

	mRotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMovement"));
	mRotMovement->SetUpdatedComponent(mRotation);
	// Load Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (true == MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	// Use Controller Rotation
	bUseControllerRotationYaw = true;

	// Load BP ClassInfo
	// Path(Reference Copy) + "_C"를 꼭 붙여줘야함
	static ConstructorHelpers::FClassFinder<AActor> AttackClass(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestActor.BP_TestActor_C'"));

	if (AttackClass.Succeeded())
	{
		mAttackClass = AttackClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> ShieldClass(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestShield.BP_TestShield_C'"));

	if (ShieldClass.Succeeded())
	{
		mShieldClass = ShieldClass.Class;
	}
}

// Called when the game starts or when spawned
void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// GetController()->IsPlayerController();
	// Cast == dynamic_cast
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

	if (!mSkillFlag.EnableShield)
	{
		mShieldTime += DeltaTime;

		if (mShieldTime >= mShieldCoolDown)
		{
			mSkillFlag.EnableShield = true;
			mShieldTime = 0.f;
		}
	}
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

		EnhancedInputComponent->BindAction(
			InputData->mTripleShot,
			ETriggerEvent::Started,
			this,
			&ACTestPlayerCharacter::TripleShotAction);
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

	// AddOnScreenDebugMessage == 뷰포트에 원하는 문자열을 출력해주는 함수
	// 1. Key == -1 넣으면 됨 << 지금은 알필요 X
	// 2. TimeToDisplay == 몇 초 화면에 띄울것이냐
	// 3. FColor == UE의 색상시스템 RGB(255,255,255)A(255)
	// 4. FString == 출력하고자 하는 String
	// * FString == (Unicode)UE에서 쓰는 문자열 클래스
	// * Printf == 화면에 문자열 출력 X / 문자열을 만들어 주는 함수
	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("X : %f Y : %f"), Axis.X, Axis.Y));

	AddControllerYawInput(Axis.X);

	float _Delta = GetWorld()->GetDeltaSeconds();
	mArm->AddRelativeRotation(FRotator(Axis.Y * 90.0 * _Delta, 0.0, 0.0));
}

void ACTestPlayerCharacter::AttackAction(const FInputActionValue& Value)
{
	// BP클래스 끌어쓰는 방법
	// 1. #include가 먼저 되어야함 << 근데 BP가 헤더파일이 있어?? X
	//	   << UClass 정보를 가져와야함
	//     << FClassFinder == 객체의 UClass정보를 가져옴 != FObjectFinder (객체를 가져옴)
	//	   그렇게 해당 Class정보를 가져와서 해당 객체타입(지금은 BPClass)으로 Actor를 만들 수 있음
	//	   그렇지만 마우스 클릭을 누를 떄 마다 UClass 정보를 가져올 필요는 없음 << 한번만 불러오면 됨
	//	   TSubclassOf : UClass 정보를 저장하는 템플릿 객체이다.

	FVector Location = GetActorLocation() + GetActorForwardVector() * 100.f;

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	GetWorld()->SpawnActor<AActor>(mAttackClass, Location, GetActorRotation(), Param);
}

void ACTestPlayerCharacter::ShieldAction(const FInputActionValue& Value)
{
	// C++코드로 액터 생성 방법
	// #include "CTestPlayerPawn.h"
	// GetWorld()->SpawnActor<ACTestPlayerPawn>();

	 if (!mSkillFlag.EnableShield)
	 {
		return;
	 }

	 mSkillFlag.EnableShield = false;
	 mShieldTime = 0.f;

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;

	FVector ShieldLocation = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	for (int32 i = 0; i < 4; i++)
	{
		switch (i)
		{	
		case 0:
			ShieldLocation = GetActorLocation() + GetActorForwardVector() * 200.0;
			Rot.Yaw = 0.0;
			break;
		case 1:
			ShieldLocation = GetActorLocation() + GetActorForwardVector() * -200.0;
			Rot.Yaw = 180.0;
			break;
		case 2:
			ShieldLocation = GetActorLocation() + GetActorRightVector() * 200.0;
			Rot.Yaw = 90.0;
			break;
		case 3:
			ShieldLocation = GetActorLocation() + GetActorRightVector() * -200.0;
			Rot.Yaw = 270.0;
			break;
		default:
			// Error
			break;
		}
		AActor* _CurShield = GetWorld()->SpawnActor<ACTestShield>(ACTestShield::StaticClass(), ShieldLocation, GetActorRotation() + Rot, Param);
		_CurShield->AttachToComponent(mRotation, FAttachmentTransformRules::KeepWorldTransform);
	}  

	// 위 결과와 아래 결과 다름 X -> 회전값의 차이 발생
	// 왜 ? 나중에 물어보자
	//for (int32 i = 0; i < 4; i++)
	//{
	//	switch (i)
	//	{
	//	case 0:
	//		ShieldLocation = GetActorForwardVector() * 200.0;
	//		Rot.Yaw = 0.0;
	//		break;
	//	case 1:
	//		ShieldLocation = GetActorForwardVector() * -200.0;
	//		Rot.Yaw = 180.0;
	//		break;
	//	case 2:
	//		ShieldLocation = GetActorRightVector() * 200.0;
	//		Rot.Yaw = 90.0;
	//		break;
	//	case 3:
	//		ShieldLocation = GetActorRightVector() * -200.0;
	//		Rot.Yaw = 270.0;
	//		break;
	//	default:
	//		// Error
	//		break;
	//	}
	//	AActor* _CurShield = GetWorld()->SpawnActor<ACTestShield>(ACTestShield::StaticClass(), ShieldLocation, Rot, Param);
	//	_CurShield->AttachToComponent(mRotation, FAttachmentTransformRules::KeepRelativeTransform);
	//}
}

void ACTestPlayerCharacter::TripleShotAction(const FInputActionValue& Value)
{
	FVector BulletLocation = GetActorLocation() + 
		GetActorForwardVector() * 100.f + 
		GetActorRightVector() * -100.f;

	FRotator BulletRot = FRotator::ZeroRotator;
	BulletRot.Yaw -= 45.f;

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;

	for (int i = 0; i < 3; i++)
	{
		GetWorld()->SpawnActor<AActor>(mAttackClass, BulletLocation + GetActorRightVector() * i * 100.f, GetActorRotation() + BulletRot + FRotator(0.0, i * 45.f, 0.0), Param);
	}
}
