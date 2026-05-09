// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TaskMonitor.h"
#include "GameSetting/PlayerBattleController.h"

// Sets default values
ATaskMonitor::ATaskMonitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATaskMonitor::BeginPlay()
{
	Super::BeginPlay();
	Mission_copy = Mission;
	for (auto& mission:Mission_copy)
	{
		if (mission.MissonType==EMissionType::TimerOut)
		{
			Local_Timer = mission.Progress;
		}
		mission.Progress = 0;
	}
	PlayerController =Cast<APlayerBattleController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->TaskMonitor = this;
		if (Local_Timer>=0)
		{
			PlayerController->LaunchTimer(Local_Timer);
		}
	}
}

// Called every frame
void ATaskMonitor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLaunch && PlayerController)
	{
		TCProgressDecreaseByController(PlayerController->GetRemainingTime());
	}
}

void ATaskMonitor::MissionComplete(bool IsComplete)
{
	IsLaunch = false;
	PlayerController->StopTimer();
	MissionCompleteBroad.Broadcast(IsComplete);
	//Destroy(this);
}

void ATaskMonitor::TrackMissionProgressAdd(EMissionType MissionType, float Progress)
{
	for (auto& mission : Mission_copy)
	{
		if (mission.MissonType==MissionType)
		{
			mission.Progress += Progress;
			for (const auto&TargetMission:Mission)
			{
				if (TargetMission.MissonType==MissionType)
				{
					if (mission.Progress >= TargetMission.Progress)
					{
						MissionComplete(true);
					}
				}
			}
			
			break;
		}
	}
}

void ATaskMonitor::TCProgressDecreaseByController(float Timer)
{
	if (Timer <= -1)
		return;

	if (Timer<0.001)
	{
		MissionComplete(false);
	}
}

