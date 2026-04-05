// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/HealthInterface.h"
#include "HealthComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBroadDeath);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//死亡事件
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FBroadDeath BroadDeath;

	UFUNCTION(BlueprintCallable)
	void OnBroadDeath();
	//基础设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Defence = 100;


	//调用函数
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



private:
	float CurrentHealth = 100.f;
	
	IHealthInterface* HealthInterface;

	void DeathDelegate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

		
public:
	//重新设置生命
	UFUNCTION(BlueprintCallable)
	void ReSetMaxHealth(float value,bool IsCurrentGetMax);

	//增加新的生命上限
	UFUNCTION(BlueprintCallable)
	void AddMaxHealth(float value, bool IsCurrentGetMax);
};
