// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitStopComp.generated.h"

class UCameraComponent;

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

	//全局时停+摄像机放大
	UFUNCTION(BlueprintCallable)
	void CameraFOVDecrease(UCameraComponent*Camera,float target,float Speed);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FTimerHandle HitStopWorldTimeHandle;
	FTimerHandle HitStopLocalTimeHandle;

	FTimerHandle CameraFOVHandle;

	void CameraDecrease();
	void CameraDecreaseLoop();
	UCameraComponent* CameraComp;
	float CameraTarget;
	float CameraSpeed;
		
};
