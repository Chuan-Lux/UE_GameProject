// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"    
#include "ToolActor.generated.h"

UCLASS()
class GAMEPROJECT_API AToolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AToolActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	//´¥·¢Æ÷
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
	USphereComponent* CollisionSphere;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Score")
	float Score;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnTrigger();
	virtual void OnTrigger_Implementation();

private:
	UPROPERTY()
	bool IsTrigger;


public:
	UPROPERTY(BlueprintReadWrite, Category = "Score")
	float LimitTime=10.f;
};
