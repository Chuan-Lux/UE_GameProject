// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/HitStopComp.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UHitStopComp::UHitStopComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitStopComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitStopComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHitStopComp::HitStopWorldTime(float Dilation, float duration)
{
	if (!GetWorld())
		return;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), Dilation);
	//清除旧的计时器
	GetWorld()->GetTimerManager().ClearTimer(HitStopWorldTimeHandle);

	//计算时停时间
	float SlowTime = duration * Dilation;


	//绑定委托，结束后执行
	FTimerDelegate HitStopWorldTimeDelegate;
	HitStopWorldTimeDelegate.BindLambda([this]
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		});

	FTimerManagerTimerParameters TimerParams;
	TimerParams.FirstDelay = -1.0;
	TimerParams.bLoop = false;

	GetWorld()->GetTimerManager().SetTimer(
		HitStopWorldTimeHandle,
		HitStopWorldTimeDelegate,
		SlowTime,
		TimerParams
	);
}

void UHitStopComp::HitStopLocalTime(float Dilation, float duration)
{
	if (!GetWorld())
		return;
	//设置角色速率
	AActor* Owner = GetOwner();
	if (Owner == nullptr)
	{
		return;
	}
	Owner->CustomTimeDilation = Dilation;



	FTimerDelegate HitStopLocalTimeDelegate;
	HitStopLocalTimeDelegate.BindLambda([this]
		{
			GetOwner()->CustomTimeDilation = 1.0f;
		});

	FTimerManagerTimerParameters TimerParams;
	TimerParams.FirstDelay = -1.0;
	TimerParams.bLoop = false;

	GetWorld()->GetTimerManager().SetTimer(
		HitStopLocalTimeHandle,
		HitStopLocalTimeDelegate,
		duration,
		TimerParams
	);
}

