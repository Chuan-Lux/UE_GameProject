// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/PaperZDEnemy.h"
#include "ActorComponent/HealthComp.h"
#include "ActorComponent/InputRecorderComp.h"
#include "ActorComponent/GethitComp.h"



APaperZDEnemy::APaperZDEnemy()
{
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	InputRecorderComp = CreateDefaultSubobject<UInputRecorderComp>(TEXT("InputRecorderComp"));
	GethitComp = CreateDefaultSubobject<UGethitComp>(TEXT("GethitComp"));
}

void APaperZDEnemy::OnDeath_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("¹ÖÎïËÀÍö"));
	this-> Destroy();
}

void APaperZDEnemy::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force, const float& Damage,bool bIsCritical)
{
}
