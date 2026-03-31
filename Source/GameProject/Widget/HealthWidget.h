// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UProgressBar* Real_Bar;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UProgressBar* Virtual_Bar;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	float Health_Virtual_Speed=0.002f;

	UFUNCTION(BlueprintCallable)
	void SetVirtualHealth();

private:
	bool ConstractHealtnBar();

	void Continue();
	FTimerHandle FrameDelayTimerHandle;
};
