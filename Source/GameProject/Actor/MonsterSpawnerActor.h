// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"    
#include "Components/BoxComponent.h"    
#include "MonsterSpawnerActor.generated.h"

class APaperZDEnemy;

USTRUCT(BlueprintType)
struct FMonsterSpawner
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APaperZDEnemy> Enemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* SpawnCurve=nullptr;

	float CurrentTime=0;
	float CurrentEnemy;

	//根据曲线时间点返回数量
	int GetTargetSpawnCountAtTime(float Time) const
	{
		if (!SpawnCurve)
		{
			return 0;
		}

		float CurveValue = SpawnCurve->GetFloatValue(Time);
		return FMath::RoundToInt(CurveValue);
	}
};


UCLASS()
class GAMEPROJECT_API AMonsterSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnerActor();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Monster")
	UBoxComponent* SpwnBoxComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//刷怪数组
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Monster")
	TArray<FMonsterSpawner> Monsters;


private:
	//获取随机点
	FVector GetRandomPointInBoxComponent();

	//生成Enemy
	void SpawnEnemy(TSubclassOf<APaperZDEnemy> Enemyclass);

	void UpdateSpawn(float deltatime);


	//计时器
	UPROPERTY()
	float MaxTimer=0;
	UPROPERTY()
	float GlobalTimer = 0;

	
};

