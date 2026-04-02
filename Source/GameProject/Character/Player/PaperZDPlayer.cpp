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

void APaperZDPlayer::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force, const float& Damage,bool bIsCritical)
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

FDamageStruct APaperZDPlayer::GetCharacterBasicData(EAttackType AttackType)
{
	FDamageStruct Stats;
	Stats.ATK = ATK;
	Stats.CR = Critical_Rate;
	Stats.CD = Critical_Damage;
	switch (AttackType)
	{
	case EAttackType::None:
		Stats.Increase = 1;
		break;
	case EAttackType::Melee:
		Stats.Increase = Melee_Damage_Increase;
		break;
	case EAttackType::Ranged:
		Stats.Increase = Ranged_Damage_Increase;
		break;
	default:
		break;
	}
	return Stats;
}
