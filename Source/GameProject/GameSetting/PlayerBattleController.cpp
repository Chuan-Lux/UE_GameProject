// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/PlayerBattleController.h"
#include "ActorComponent/GlobalTimerComp.h"


APlayerBattleController::APlayerBattleController()
{
	GlobalTimerComp = CreateDefaultSubobject<UGlobalTimerComp>(TEXT("GlobalComp"));
}

void APlayerBattleController::LaunchTimer(float time)
{
	GlobalTimerComp->Timer = time;
	GlobalTimerComp->LaunchTimer();
}

float APlayerBattleController::GetRemainingTime()
{
	return GlobalTimerComp->GetRemainingTime();
}
