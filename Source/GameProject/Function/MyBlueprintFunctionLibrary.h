// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperCharacter.h"
#include "MyClass.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable, Category = "Character")
	static void TickRotation(APaperCharacter*Character);

	//世界坐标向量转换为局部向量
	UFUNCTION(BlueprintPure)
	static FVector Vector_WorldCastToLocal(AActor* Target, FVector WorldVector);

	UFUNCTION(BlueprintPure)
	static FVector Vector_LocalCastToWorld(AActor* Target, FVector LocalVector);

	//UI朝向摄像机
	UFUNCTION(BlueprintCallable, Category = "Character")
	static void WidgetToCamera(USceneComponent* Widget);

	//角色朝向摄像机
	UFUNCTION(BlueprintCallable, Category = "Character")
	static void ActorToCamera(AActor* Source);
	////根据方向选择动画
	//UFUNCTION(BlueprintPure)
	//static UPaperZDAnimSequence* PaperAnim();


	//伤害计算
	UFUNCTION(BlueprintPure)
	static float DamageCalculation(const float ATK, const float Increase, const float Critical_Rate, const float Critical_Damage,bool& bIsCritical);

	//执行Notify
	UFUNCTION(BlueprintCallable, Category = "Notify")
	static void ExcuteNotify(const UObject* WorldContextObject, TSubclassOf<UEffectNotify> NotifyClass);

	//增加 IndexNum;
	UFUNCTION(BlueprintCallable, Category = "Data")
	static TArray<FIndexNum> InsertData(TArray<FIndexNum> List, int Index, int num);
	//减少
	UFUNCTION(BlueprintCallable, Category = "Data")
	static TArray<FIndexNum> RemoveData(TArray<FIndexNum>List,int Index, int num);
};
