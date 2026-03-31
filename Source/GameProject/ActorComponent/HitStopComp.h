// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitStopComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UHitStopComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitStopComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HitStopWorldTime(float Dilation, float duration);

	UFUNCTION(BlueprintCallable)
	void HitStopLocalTime(float Dilation, float duration);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FTimerHandle HitStopWorldTimeHandle;
	FTimerHandle HitStopLocalTimeHandle;
		
};
