// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MonsterSpawnerActor.h"

// Sets default values
AMonsterSpawnerActor::AMonsterSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpwnBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerBox"));
}

// Called when the game starts or when spawned
void AMonsterSpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	//初始化enemy信息
	for (FMonsterSpawner& Monster : Monsters)
	{
		Monster.CurrentEnemy = 0;
		Monster.CurrentTime = 0.0f;

		float MinTime, MaxTime;
		Monster.SpawnCurve->GetTimeRange(MinTime, MaxTime);
		if (MaxTime>MaxTimer)
		{
			MaxTimer = MaxTime;
		}
	}
}

// Called every frame
void AMonsterSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateSpawn(DeltaTime);
}

FVector AMonsterSpawnerActor::GetRandomPointInBoxComponent()
{
    if (!SpwnBoxComp)
    {
        return FVector::ZeroVector;
    }

    FBoxSphereBounds Bounds = SpwnBoxComp->Bounds;
    FBox BoxBounds = Bounds.GetBox();
    FVector RandomPoint = FMath::RandPointInBox(BoxBounds);

    return RandomPoint;
}

void AMonsterSpawnerActor::SpawnEnemy(TSubclassOf<APaperZDEnemy> Enemyclass)
{
	UWorld* World = GetWorld();
	if (IsValid(World))
	{
		//生成
		APaperZDEnemy* SpawnedActor = World->SpawnActor<APaperZDEnemy>(Enemyclass, GetRandomPointInBoxComponent(), FRotator().ZeroRotator);
	}
}

void AMonsterSpawnerActor::UpdateSpawn(float deltatime)
{
	if (GlobalTimer<=MaxTimer)
	{
		GlobalTimer += deltatime;
		for (FMonsterSpawner& Monster : Monsters)
		{
			if (!Monster.Enemy || !Monster.SpawnCurve)
				continue;

			float Min, Max;
			Monster.SpawnCurve->GetTimeRange(Min, Max);
			if (GlobalTimer> Max)
				continue;

			//获取当前生成数量
			int AllSpawnNum = Monster.GetTargetSpawnCountAtTime(GlobalTimer);
			if (AllSpawnNum <= 0)
				continue;

			int NeedNum = AllSpawnNum - Monster.CurrentEnemy;
			for (int32 i = 0; i <NeedNum; i++)
			{
				SpawnEnemy(Monster.Enemy);
			}
			Monster.CurrentEnemy = AllSpawnNum;
		}
	}
	
}

