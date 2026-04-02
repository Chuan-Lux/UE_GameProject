// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "MyClass.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	None  UMETA(DisplayName = "None"),
	Center UMETA(DisplayName = "Center"),
	Up    UMETA(DisplayName = "Up"),
	Down  UMETA(DisplayName = "Down"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Up_Left UMETA(DisplayName = "Up_Left"),
	Up_Right UMETA(DisplayName = "Up_Right"),
	Down_Left UMETA(DisplayName = "Down_Left"),
	Down_Right UMETA(DisplayName = "Down_Right")
	
};

UENUM(BluePrintType)
enum class ECharacterState :uint8 
{
	None  UMETA(DisplayName = "None"),
	GetHit  UMETA(DisplayName = "GetHit"),
	Dead UMETA(DisplayName = "Dead"),
	Defence UMETA(DisplayName = "Defence"),
	Invincible UMETA(DisplayName = "Invincible"),
	PerfectDodge UMETA(DisplayName = "PerfectDodge")
};

//好友名称
UENUM(BluePrintType)
enum class EPartner :uint8
{
	None UMETA(DisplayName = "None"),
};


//成长数值
UENUM(BluePrintType)
enum class EGrowthData :uint8
{
	None UMETA(DisplayName = "None"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Dedication UMETA(DisplayName = "Dedication"),
	Prestige UMETA(DisplayName = "Prestige"),
	Purchasing UMETA(DisplayName = "Purchasing"),
	Stamina UMETA(DisplayName = "Stamina")
};

UENUM(BluePrintType)
enum class EAttackType:uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged")
};


USTRUCT(BlueprintType)
struct FDamageStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ATK = 0.0f;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Increase = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CR = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CD = 0.0f;
};

class GAMEPROJECT_API MyClass
{
public:
	MyClass();
	~MyClass();
};
