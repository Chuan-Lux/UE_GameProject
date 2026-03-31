// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Defence = 100;

	UFUNCTION(BlueprintCallable)
	void LoseHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void CureHealth(float Amount);

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() 
	{
		return CurrentHealth;
	}

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() 
	{
		return CurrentHealth / MaxHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth()
	{
		return MaxHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "GitHit")
	void OnHitOffset(FVector HitDir,float Force,float Duration);

	UFUNCTION()
	void UpdateHitOffset();

private:
	float CurrentHealth = 100.f;

	//ÊÜ»÷¼ÆÊ±Æ÷
	FTimerHandle GetHitTimeHandle;
	float ElapsedTime;
	float ElapsedDuration;
	FVector Offset;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

		
};
