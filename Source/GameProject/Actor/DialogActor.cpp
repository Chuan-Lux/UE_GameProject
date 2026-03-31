// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DialogActor.h"

// Sets default values
ADialogActor::ADialogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADialogActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogActor::OnEvent_Implementation()
{
}

