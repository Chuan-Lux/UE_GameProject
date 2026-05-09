// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/EffectNotify.h"




APlayerController* UEffectNotify::GetPlayerController()
{
    return	GetWorld()->GetFirstPlayerController();
}

ACharacter* UEffectNotify::GetPlayer()
{
    return GetPlayerController()->GetCharacter();
}

void UEffectNotify::NotifyBegin_Implementation()
{
}

void UEffectNotify::NotifyEnd_Implementation()
{
}
