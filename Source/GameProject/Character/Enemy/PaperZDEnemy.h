// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/HealthComp.h"
#include "ActorComponent/InputRecorderComp.h"
#include "Interface/HealthInterface.h"
#include "PaperZDCharacter.h"
#include "PaperZDEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API APaperZDEnemy : public APaperZDCharacter,public IHealthInterface
{
	GENERATED_BODY()

public:
	APaperZDEnemy();

	virtual void OnDeath_Implementation() override;

	virtual void OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ACharacter* Target;

	UPROPERTY(BlueprintReadWrite, Category = "Move")
	bool IsAbleMevement=true;



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputRecorderComp* InputRecorderComp;

	
};
