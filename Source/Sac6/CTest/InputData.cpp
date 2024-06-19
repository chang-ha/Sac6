// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	// 언리얼에서 에셋을 불러올 때 사용한다
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_Test.IMC_Test'"));

		// 정상적으로 로딩했는지 판단한다
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			// 얘가 InputContext를 들고있을것임
			mDefaultContext = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestMove.IA_TestMove'"));

		// 정상적으로 로딩했는지 판단한다
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정한다.
			// 얘가 InputContext를 들고있을것임
			mMove = Asset.Object;
		}
	}
}
