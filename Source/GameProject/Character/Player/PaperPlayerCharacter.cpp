// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PaperPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"  



void APaperPlayerCharacter::UpdateRotation()
{
	if (!GetCharacterMovement())
	{
		return;
	}

	float CurrentSpeedX = GetCharacterMovement()->Velocity.X;
	
    FRotator TargetRotation;
    float TargetScale;

    if (CurrentSpeedX > 0.1f)  
    {
        TargetRotation = FRotator(0.0f, 0.0f, 0.0f);  
        TargetScale = 1;
    }
    else if (CurrentSpeedX < -0.1f)  
    {
        TargetRotation = FRotator(0.0f, 180.f, 0.0f); 
        TargetScale = -1;
    }
    else
    {
        return;  
    }

    GetSprite()->SetWorldRotation(TargetRotation);
    //GetSprite()->SetWorldScale3D(FVector(TargetScale, 1, 1));
    //SetActorRotation(TargetRotation);
}
