// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAMEPROJECT_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    FGameplayAttributeData Defence;
    ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Defence);

    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    FGameplayAttributeData ATK;
    ATTRIBUTE_ACCESSORS(UBasicAttributeSet,ATK);

    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    FGameplayAttributeData MeleeIncrease;
    ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MeleeIncrease);

    UPROPERTY(BlueprintReadOnly, Category = "GAS")
    FGameplayAttributeData RangedIncrease;
    ATTRIBUTE_ACCESSORS(UBasicAttributeSet,RangedIncrease);

};
