// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalTimerComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGlobalTimerDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UGlobalTimerComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlobalTimerComp();

	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FGlobalTimerDelegate GlobalTimerDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(EditAnywhere, Category = "Timer")
	float Timer;

	UFUNCTION(BlueprintPure)
	float GetRemainingTime()
	{
		return RemainingTime;
	}

	UFUNCTION(BlueprintCallable)
	void LaunchTimer();

	//ÊÂ¼þ½áÊø
	UFUNCTION(BlueprintNativeEvent)
	void TimerEndEvent();
	virtual void TimerEndEvent_Implementation();

private:
	bool IsContinue;
	float RemainingTime;
	FTimerHandle TimerHandle;
};
