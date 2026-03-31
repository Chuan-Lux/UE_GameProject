// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPROJECT_API IHealthInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void OnDeath();
	virtual void OnDeath_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void OnDmg(const FHitResult& HitResult, const FVector& AttackVec, const float& Force);
	virtual void OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force) = 0;


	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void OnDef(const FHitResult& HitResult, const FVector& AttackVec, const float& Force);
	virtual void OnDef_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force) = 0;*/
};
