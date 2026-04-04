// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/GethitComp.h"
#include "PaperFlipbookComponent.h"  
#include "TimerManager.h"


// Sets default values for this component's properties
UGethitComp::UGethitComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGethitComp::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<APaperZDCharacter>(GetOwner());
	BeginLocation = Character->GetSprite()->GetRelativeLocation();
}


// Called every frame
void UGethitComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGethitComp::CharacterShake(float Amplitude, float Frequency, float duration)
{
	if (!GetWorld())
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(ShakeHandle);
	Amplitude_Local = Amplitude;
	FrequencyTime_Local = 1/Frequency;
	duration_Local = duration;


	GetWorld()->GetTimerManager().SetTimer(
		ShakeHandle,
		this,
		&UGethitComp::Shake,
		FrequencyTime_Local,
		true
	);

	//停止循环
	FTimerHandle StopShakeHandle;
	GetWorld()->GetTimerManager().SetTimer(
		StopShakeHandle,
		[this]()  // Lambda 表达式
		{
			StopShake();
		},
		duration,
		false 
	);
}

void UGethitComp::Shake()
{
	if (!Character) return;

	// 随机生成 0 到 360 度的角度
	float RandomAngle = FMath::FRandRange(0.0f, 360.0f);
	// 转换为弧度
	float Radians = FMath::DegreesToRadians(RandomAngle);

	FVector NewLocation;
	NewLocation.X = BeginLocation.X+Amplitude_Local * FMath::Cos(Radians);
	NewLocation.Z = BeginLocation.Z+Amplitude_Local * FMath::Sin(Radians);
	NewLocation.Y = BeginLocation.Y;

	// 设置相对位置
	Character->GetSprite()->SetRelativeLocation(NewLocation);
}

void UGethitComp::StopShake()
{
	if (!GetWorld())
	{
		return;
	}

	// 停止震荡计时器
	GetWorld()->GetTimerManager().ClearTimer(ShakeHandle);
	Character->GetSprite()->SetRelativeLocation(BeginLocation);
}



void UGethitComp::OnHitOffset(FVector HitDir, float Force, float Duration)
{
	GetWorld()->GetTimerManager().ClearTimer(GetHitTimeHandle);
	FVector Distance = HitDir.GetSafeNormal() * Force;

	ElapsedTime = 0.0f;
	ElapsedDuration = Duration;
	Offset = Distance;

	GetWorld()->GetTimerManager().SetTimer(
		GetHitTimeHandle,
		this,
		&UGethitComp::UpdateHitOffset,
		0.016f,
		true     // 循环
	);
}

void UGethitComp::UpdateHitOffset()
{
	ElapsedTime += 0.016f;
	GetOwner()->AddActorWorldOffset(Offset);
	if (ElapsedTime >= ElapsedDuration)
	{
		GetWorld()->GetTimerManager().ClearTimer(GetHitTimeHandle);
	}
}

