// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ToolActor.h"
#include "Character/Player/PaperZDPlayer.h"
#include "Function/MyBlueprintFunctionLibrary.h"
#include "GameSetting/PlayerBattleController.h"

// Sets default values
AToolActor::AToolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject <USphereComponent>(TEXT("Collision"));

	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AToolActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&AToolActor::OnSphereOverlap);
	
}

// Called every frame
void AToolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LimitTime -= DeltaTime;
	if (LimitTime<=0)
	{
		Destroy();
	}

	UMyBlueprintFunctionLibrary::ActorToCamera(this);
}

void AToolActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsTrigger) return;

	APaperZDPlayer* Player = Cast<APaperZDPlayer>(OtherActor);
	if (IsValid(Player))
	{
		IsTrigger = true;


		APlayerBattleController* PlayerController = Cast<APlayerBattleController>(Player->GetController());
		PlayerController->AddScore(Score);

		OnTrigger();
		//CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AToolActor::OnTrigger_Implementation()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Sphere overlapped with player!"));
}

