// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	// �𸮾󿡼� ������ �ҷ��� �� ����Ѵ�
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_Test.IMC_Test'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			// �갡 InputContext�� �����������
			mDefaultContext = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestMove.IA_TestMove'"));

		// ���������� �ε��ߴ��� �Ǵ��Ѵ�
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� ������ ��������� �����Ѵ�.
			// �갡 InputContext�� �����������
			mMove = Asset.Object;
		}
	}
}
