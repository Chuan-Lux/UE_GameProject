// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/EventInterface.h"
#include "GameFramework/Actor.h"
#include "DialogActor.generated.h"

UCLASS()
class GAMEPROJECT_API ADialogActor : public AActor,public IEventInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogActor();
	virtual void Tick(float DeltaTime) override;

	virtual void OnEvent_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
