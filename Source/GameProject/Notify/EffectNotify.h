// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectNotify.generated.h"


class APlayerController;
class ACharacter;

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class GAMEPROJECT_API UEffectNotify : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Notify")
	void  NotifyBegin();

	UFUNCTION(BlueprintPure)
	APlayerController* GetPlayerController();

	UFUNCTION(BlueprintPure)
	ACharacter* GetPlayer();

protected:
	virtual void NotifyBegin_Implementation();

};
