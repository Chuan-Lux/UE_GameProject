// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/PaperZDEnemy.h"

APaperZDEnemy::APaperZDEnemy()
{
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	InputRecorderComp = CreateDefaultSubobject<UInputRecorderComp>(TEXT("InputRecorderComp"));
}

void APaperZDEnemy::OnDeath_Implementation()
{
}

void APaperZDEnemy::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force)
{
}
