// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerBattleController.generated.h"

class UGlobalTimerComp;

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
	UFUNCTION(BlueprintPure, Category = "ClobalTimer")
	float GetRemainingTime();
};
