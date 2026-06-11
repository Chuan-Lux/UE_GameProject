// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerBattleController.generated.h"

class UGlobalTimerComp;
class ATaskMonitor;

UCLASS()
class GAMEPROJECT_API APlayerBattleController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerBattleController();

	//时间管理器
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GlobalTimer", meta = (AllowPrivateAccess = "true"))
	class UGlobalTimerComp* GlobalTimerComp;


public:
	UFUNCTION(BlueprintCallable, Category = "GlobalTimer")
	void LaunchTimer(float time);

	UFUNCTION(BlueprintCallable, Category = "GlobalTimer")
	void StopTimer();

	UFUNCTION(BlueprintPure, Category = "ClobalTimer")
	float GetRemainingTime();


	//时间任务管理器
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
	ATaskMonitor* TaskMonitor;


	//分数机制
private:
	UPROPERTY(BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
	float Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
	float KillEnemy = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(float Add)
	{
		Score += Add;
	}

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddKillEnemy(float Add)
	{
		KillEnemy+= Add;
	}

	UFUNCTION(BlueprintPure, Category = "Score")
	float GetKillEnemy()
	{
		return KillEnemy;
	}

	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetKillEnemy()
	{
		KillEnemy =0;
	}
};
