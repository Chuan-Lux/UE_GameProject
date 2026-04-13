// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/GlobalTimerComp.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UGlobalTimerComp::UGlobalTimerComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGlobalTimerComp::BeginPlay()
{
	Super::BeginPlay();

	GlobalTimerDelegate.AddDynamic(this, &UGlobalTimerComp::TimerEndEvent);
}


// Called every frame
void UGlobalTimerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsContinue)
	{
		RemainingTime -= DeltaTime;
		if (RemainingTime<=0)
		{
			RemainingTime = 0.f;
		}
	}

}

void UGlobalTimerComp::LaunchTimer()
{
	if (!GetWorld())
		return;

	//清除旧的计时器
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	RemainingTime = Timer;
	IsContinue = true;

	//绑定委托，结束后执行
	FTimerDelegate TimeDelegate;
    TimeDelegate.BindLambda([this]
		{
			//TimerEndEvent();
			GlobalTimerDelegate.Broadcast();
			IsContinue = false;
		});

	FTimerManagerTimerParameters TimerParams;
	TimerParams.FirstDelay = -1.0;
	TimerParams.bLoop = false;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		TimeDelegate,
		Timer,
		TimerParams
	);

}

void UGlobalTimerComp::TimerEndEvent_Implementation()
{
	//IsContinue = false;
}

