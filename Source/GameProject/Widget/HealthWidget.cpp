// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthWidget.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"


void UHealthWidget::SetVirtualHealth()
{
	bool IsContine=ConstractHealtnBar();
	if (IsContine)
	{
		Continue();
	}
}

bool UHealthWidget::ConstractHealtnBar()
{
	float Real_Percent=Real_Bar->GetPercent();
	float Virtual_Percent=Virtual_Bar->GetPercent();
	float Result= FMath::Max(Real_Percent, Virtual_Percent + Health_Virtual_Speed * (FMath::Sign(Real_Percent - Virtual_Percent)));
	Virtual_Bar->SetPercent(Result);
	if (Result!=Real_Percent)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UHealthWidget::Continue()
{
	GetWorld()->GetTimerManager().ClearTimer(FrameDelayTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		FrameDelayTimerHandle,
		this,
		&UHealthWidget::SetVirtualHealth,
		0.0001f,  
		false    
	);
}
