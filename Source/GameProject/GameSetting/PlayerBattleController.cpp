// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/PlayerBattleController.h"
#include "ActorComponent/GlobalTimerComp.h"
#include "Actor/TaskMonitor.h"


APlayerBattleController::APlayerBattleController()
{
	GlobalTimerComp = CreateDefaultSubobject<UGlobalTimerComp>(TEXT("GlobalComp"));
}

void APlayerBattleController::LaunchTimer(float time)
{
	GlobalTimerComp->Timer = time;
	GlobalTimerComp->LaunchTimer();
	if (TaskMonitor)
	{
		TaskMonitor->IsLaunch = true;
	}
}

void APlayerBattleController::StopTimer()
{
	GlobalTimerComp->StopTimer();
}

float APlayerBattleController::GetRemainingTime()
{
	return GlobalTimerComp->GetRemainingTime();
}
