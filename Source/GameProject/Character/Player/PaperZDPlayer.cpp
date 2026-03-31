// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PaperZDPlayer.h"

APaperZDPlayer::APaperZDPlayer()
{
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	HitStopComp = CreateDefaultSubobject<UHitStopComp>(TEXT("HitStopComp"));
	InputRecorder = CreateDefaultSubobject<UInputRecorderComp>(TEXT("InputRecorderComp"));

	NowState = ECharacterState::None;
}

void APaperZDPlayer::OnDeath_Implementation()
{
}

void APaperZDPlayer::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force)
{
}

EInputDirection APaperZDPlayer::DirectionToTaeget()
{
	if(Target!=nullptr)
	{
		InputRecorder->UpdateDirectionHistory(InputRecorder->GetTargetDirection(Target));
		return InputRecorder->VectorToDir(InputRecorder->GetTargetDirection(Target));
	}
	else
	{
		return InputRecorder->GetNowInputDirection();
	}
	
}

FVector2D APaperZDPlayer::VectorToTaeget()
{
    return InputRecorder->DirToVector(DirectionToTaeget());
}

APaperZDEnemy* APaperZDPlayer::LookForEnemy(float MaxDistance, TArray<AActor*> Actors)
{
	float CurrenDistance=MaxDistance;
	APaperZDEnemy* CurrentEnemy=nullptr;
	for (AActor* Enemy : Actors)
	{
		APaperZDEnemy* paperEnemy = Cast<APaperZDEnemy>(Enemy);
		if (paperEnemy!=nullptr)
		{
			float len = FVector::Dist2D(paperEnemy->GetActorLocation(), this->GetActorLocation());
			if (len<=CurrenDistance)
			{
				CurrenDistance = len;
				CurrentEnemy = paperEnemy;
			}
		}
	}
	return CurrentEnemy;
}
