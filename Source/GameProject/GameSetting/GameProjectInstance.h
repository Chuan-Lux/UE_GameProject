// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyClass.h"
#include "GameProjectInstance.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateDayProgress, int32, Day, int32, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateGrowthData);

UCLASS()
class GAMEPROJECT_API UGameProjectInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Calendar")
	int DayTime=1;

	UPROPERTY(BlueprintReadWrite, Category = "Calendar")
	int ProgressPoint;


	//节点时间分发器
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUpdateDayProgress OnUpdateDayProgress;
	//养成系统分发器
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUpdateGrowthData UpdateGrowthData;



	UFUNCTION(BlueprintCallable, Category = "Event")
	void TriggerEvent_UpdateDayProgress(int Day,int Progress);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void TriggerEvent_UpdateGrowthData();

	//检测
	UFUNCTION(BlueprintCallable, Category = "Event")
	void CheckOutTime();

	//进度调整
	UFUNCTION(BlueprintCallable, Category = "Event")
	void AddCalendar(int Add_Day,int Add_Progress);

private:
	int Last_Day;
	int Last_Progress;


	//养成系统
public:
	UPROPERTY(BlueprintReadWrite, Category = "Growth")
	float Multiplier_Int=1;
	UPROPERTY(BlueprintReadWrite, Category = "Growth")
	float Multiplier_Ded=1;
	UPROPERTY(BlueprintReadWrite, Category = "Growth")
	float Multiplier_Prestige=1;
	UPROPERTY(BlueprintReadWrite, Category = "Growth")
	float Multiplier_Purchasing=1;
	UPROPERTY(BlueprintReadWrite, Category = "Growth")
	float Multiplier_STA=1;

	UFUNCTION(BlueprintCallable)
	void Increase_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA);

	UFUNCTION(BlueprintCallable)
	void Decrease_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA);

	void Time_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA);

	UFUNCTION(BlueprintPure)
	float AddAbility(float BasicValue, float AddValue, const EGrowthData GrowthData);
};
