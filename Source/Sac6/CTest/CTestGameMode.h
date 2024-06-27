// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "CTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAC6_API ACTestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACTestGameMode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 mScore = 0;

public:
	void AddScore(int32 _Score)
	{
		mScore += _Score;
		UE_LOG(Sac6, Warning, TEXT("Score : %d"), mScore);
	}
};
