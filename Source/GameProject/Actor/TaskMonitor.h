// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass.h"
#include "TaskMonitor.generated.h"

class APlayerBattleController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMissionComplete, bool, IsComplete);

UCLASS()
class GAMEPROJECT_API ATaskMonitor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskMonitor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//任务数值设置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
	TArray<FMissionStruct> Mission;

	UPROPERTY(BlueprintReadOnly, Category = "Mission")
	TArray<FMissionStruct> Mission_copy;

	//任务事件
	UPROPERTY(BlueprintAssignable, Category = "Mission")
	FMissionComplete MissionCompleteBroad;

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void MissionComplete(bool IsComplete);

	//添加任务节点
	UFUNCTION(BlueprintCallable, Category = "Mission")
	void TrackMissionProgressAdd(EMissionType MissionType, float Progress);

	//返回任务进度百分比
	UFUNCTION(BlueprintPure, Category = "Mission")
	float ReturnProgressElimination();

	UFUNCTION(BlueprintImplementableEvent)
	void EventEnd();

	//绑定到controller 的计时器
	UFUNCTION(BlueprintCallable, Category = "Mission")
	void TCProgressDecreaseByController(float Timer);

	UPROPERTY();
	bool IsLaunch;

	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mission", meta = (AllowPrivateAccess = "true"))
	float Local_Timer = -1;
	
	UPROPERTY()
	APlayerBattleController* PlayerController;
};
