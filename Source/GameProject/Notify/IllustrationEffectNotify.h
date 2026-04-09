// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notify/EffectNotify.h"
#include "IllustrationEffectNotify.generated.h"


class UTexture2D;
class UUserWidget;

UCLASS()
class GAMEPROJECT_API UIllustrationEffectNotify : public UEffectNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "illustration")
	UTexture2D* illustration;

	UFUNCTION(BlueprintCallable)
	void Set_illustration_Widget(UUserWidget* NowWidget)
	{
		illustration_Widget = NowWidget;
	}
	UFUNCTION(BlueprintPure)
	UUserWidget* Get_illustration_Widget() 
	{
		return illustration_Widget;
	}

	
private:
	UPROPERTY(EditAnywhere,Category = "Widget")
	UUserWidget* illustration_Widget;

};
