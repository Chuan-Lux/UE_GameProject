// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/HealthComp.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComp::OnHitOffset(FVector HitDir, float Force, float Duration)
{
	GetWorld()->GetTimerManager().ClearTimer(GetHitTimeHandle);
	FVector Distance = HitDir.GetSafeNormal() * Force;

	ElapsedTime = 0.0f;
	ElapsedDuration = Duration;
	Offset = Distance;

	GetWorld()->GetTimerManager().SetTimer(
		GetHitTimeHandle,
		this,
		&UHealthComp::UpdateHitOffset,
		0.016f,
		true     // Ñ­»·
	);
}

void UHealthComp::UpdateHitOffset()
{
	ElapsedTime += 0.016f;
	GetOwner()->AddActorWorldOffset(Offset);
	if (ElapsedTime>=ElapsedDuration)
	{
		GetWorld()->GetTimerManager().ClearTimer(GetHitTimeHandle);
	}
}

// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

void UHealthComp::ReSetMaxHealth(float value, bool IsCurrentGetMax)
{
	MaxHealth = value;
	if (IsCurrentGetMax)
	{
		CurrentHealth = MaxHealth;
	}
	else
	{
		return;
	}
}

void UHealthComp::AddMaxHealth(float value, bool IsCurrentGetMax)
{
	MaxHealth += value;
	if (IsCurrentGetMax)
	{
		CurrentHealth = MaxHealth;
	}
	else
	{
		CurrentHealth += value;
	}
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComp::OnBroadDeath()
{
	BroadDeath.Broadcast();
}

void UHealthComp::LoseHealth(float Amount)
{
	//CurrentHealth -= CalculateDamage(Amount);
	CurrentHealth -= Amount;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		OnBroadDeath();
	}
}

void UHealthComp::CureHealth(float Amount)
{
	CurrentHealth += Amount;
	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

