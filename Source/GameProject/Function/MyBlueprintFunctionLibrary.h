// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperCharacter.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable)
	static void TickRotation(APaperCharacter*Character);

	//世界坐标向量转换为局部向量
	UFUNCTION(BlueprintPure)
	static FVector Vector_WorldCastToLocal(AActor* Target, FVector WorldVector);

	//UI朝向摄像机
	UFUNCTION(BlueprintCallable)
	static void WidgetToCamera(USceneComponent* Widget);

	//伤害计算
	UFUNCTION(BlueprintPure)
	static float DamageCalculation(const float ATK, const float Increase, const float Critical_Rate, const float Critical_Damage,bool& bIsCritical);
	
};
