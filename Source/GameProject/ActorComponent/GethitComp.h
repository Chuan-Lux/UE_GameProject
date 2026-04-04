// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperZDCharacter.h"
#include "GethitComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UGethitComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGethitComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//角色受击抖动
	UFUNCTION(BlueprintCallable)
	void CharacterShake(float Amplitude,float Frequency ,float duration);

private:

	void Shake();
	void StopShake();

	//抖动计时器
	FTimerHandle ShakeHandle;
	float Amplitude_Local;
	float FrequencyTime_Local;
	float duration_Local;

	APaperZDCharacter* Character;
	FVector BeginLocation;

	//位移
public:

	UFUNCTION(BlueprintCallable, Category = "GitHit")
	void OnHitOffset(FVector HitDir, float Force, float Duration);

	UFUNCTION()
	void UpdateHitOffset();

private:

	//受击计时器
	FTimerHandle GetHitTimeHandle;
	float ElapsedTime;
	float ElapsedDuration;
	FVector Offset;



};
