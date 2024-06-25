// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "UObject/NoExportTypes.h"
#include "InputData.generated.h"

// #include "InputMappingContext.h"
// #include "InputAction.h"

/**
 * 
 */
UCLASS()
class SAC6_API UTestInputData : public UObject
{
	GENERATED_BODY()
	
public:
	UTestInputData();

public:
	UInputMappingContext* mDefaultContext = nullptr;
public:
	UInputAction* mMove = nullptr;
	UInputAction* mRotation = nullptr;
	UInputAction* mAttack = nullptr;
	UInputAction* mShield = nullptr;
};
