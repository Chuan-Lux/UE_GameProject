// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ToolSpawnActor.h"

// Sets default values
AToolSpawnActor::AToolSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpwnBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnComp"));

	SpwnBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AToolSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if (!IsFirstSpawn)
	{
		Timeout = GetRandom(IntervalTime,RandomTime.Min,RandomTime.Max);
	}
}

// Called every frame
void AToolSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Duration -= DeltaTime;
	Timeout -= DeltaTime;
	if (Duration<=0)
	{
		Destroy();
	}
	if (Timeout<=0)
	{
		SpawnTool();
		Timeout = GetRandom(IntervalTime, RandomTime.Min, RandomTime.Max);
	}
}

float AToolSpawnActor::GetRandom(float Count, float Min, float Max)
{
	float RandomFloat = FMath::FRandRange(-Min, Max);
	float Random = Count + RandomFloat;
	if (Random<=0)
	{
		Random =0;
	}
	return Random;
}

void AToolSpawnActor::SpawnTool()
{
	float SpawnNum= GetRandom(Num, RandomNum.Min, RandomNum.Max);
	while (SpawnNum>=0)
	{
		FVector SpawnLocation = GetRandomPointInBoxComponent();
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Tool,SpawnLocation, FRotator().ZeroRotator);
		SpawnNum -= 1;
	}
}

FVector AToolSpawnActor::GetRandomPointInBoxComponent()
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

