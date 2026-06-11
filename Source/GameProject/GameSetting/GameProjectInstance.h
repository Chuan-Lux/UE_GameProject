// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyClass.h"
#include "GameProjectInstance.generated.h"

USTRUCT(BlueprintType)
struct FFans
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"))
	float Redfan=0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (ClampMin = "0", ClampMax = "100"))
	float Blackfan=0.0f;
};
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
	//粉丝管理数据
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "GrowthData")
	FFans Fan;

	UFUNCTION(BlueprintCallable, Category = "GrowthData")
	void AddFans(const float Red,const float Black);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Calendar")
	int DayTime=1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Calendar")
	int ProgressPoint=2;

	//确保事件不会重复触发
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
	bool IsChangeScenceBroadPlayer_Day=true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
	bool IsChangeScenceBroadPlayer_Progress = true;

	//节点时间分发器
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUpdateDayProgress OnUpdateDayProgress;
	//养成系统分发器
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FUpdateGrowthData UpdateGrowthData;



	UFUNCTION(BlueprintCallable, Category = "Event")
	void TriggerEvent_UpdateGrowthData();

	

	//检测
	UFUNCTION(BlueprintCallable, Category = "Event")
	void CheckOutTime();

	//进度调整
	UFUNCTION(BlueprintCallable, Category = "Event")
	void AddCalendar(int Add_Day,int Add_Progress);

private:
	int Last_Day=0;
	int Last_Progress=-1;

	//天数更新事件触发器
	void TriggerEvent_UpdateDayProgress(int Day, int Progress);


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
	float AddAbility(float BasicValue, float AddValue, const EGrowthData GrowthData,float Multipy);
};
