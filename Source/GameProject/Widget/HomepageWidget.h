// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyClass.h"
#include "HomepageWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHomepageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float SP;


};
