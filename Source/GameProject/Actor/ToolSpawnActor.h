// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"    
#include "MyClass.h"
#include "ToolSpawnActor.generated.h"


UCLASS()
class GAMEPROJECT_API AToolSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToolSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
	UBoxComponent* SpwnBoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> Tool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	bool IsFirstSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn|Time")
	float Duration=10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn|Time")
	float IntervalTime = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn|Time")
	FMaxandMin RandomTime;

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn|Num")
	int Num = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn|Num")
	FMaxandMin RandomNum;


private:
	float Timeout;

	float GetRandom(float Count,float Min,float Max);

	void SpawnTool();
	//获取随机点
	FVector GetRandomPointInBoxComponent();
};
