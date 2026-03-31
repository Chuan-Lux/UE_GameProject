// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/HealthComp.h"
#include "ActorComponent/HitStopComp.h"
#include "ActorComponent/InputRecorderComp.h"
#include "Character/Enemy/PaperZDEnemy.h"
#include "Interface/HealthInterface.h"
#include "MyClass.h"
#include "PaperZDCharacter.h"
#include "PaperZDPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API APaperZDPlayer : public APaperZDCharacter,public IHealthInterface
{
	GENERATED_BODY()

public:
	APaperZDPlayer();

	virtual void OnDeath_Implementation() override;

	virtual void OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force);

	//////Function
	//设置碰撞方向；
	UFUNCTION(BlueprintPure)
	EInputDirection DirectionToTaeget();
	//设置攻击方向
	UFUNCTION(BlueprintPure)
	FVector2D VectorToTaeget();
	//寻找敌方目标
	UFUNCTION(BlueprintCallable)
	APaperZDEnemy* LookForEnemy(float MaxDistance, TArray<AActor*>Actors);


	////Property	
	//角色状态设置
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterState NowState;

	UPROPERTY(BlueprintReadWrite, Category = "Move")
	bool IsAbleMevement=true;

	UPROPERTY(BlueprintReadWrite, Category = "Target")
	AActor* Target;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	class UHitStopComp* HitStopComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InputRecoder", meta = (AllowPrivateAccess = "true"))
	class UInputRecorderComp*InputRecorder;

	
};
