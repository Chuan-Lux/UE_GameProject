// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/GameProjectInstance.h"

void UGameProjectInstance::TriggerEvent_UpdateDayProgress(int Day, int Progress)
{
	OnUpdateDayProgress.Broadcast(Day,Progress);
}

void UGameProjectInstance::TriggerEvent_UpdateGrowthData()
{
	UpdateGrowthData.Broadcast();
}

void UGameProjectInstance::CheckOutTime()
{
	if (DayTime!=Last_Day)
	{
		ProgressPoint = 0;
		Last_Day = DayTime;
		TriggerEvent_UpdateDayProgress(DayTime, ProgressPoint);
	}
	else
	{
		if (ProgressPoint>Last_Progress)
		{
			Last_Progress = ProgressPoint;
			TriggerEvent_UpdateDayProgress(DayTime, ProgressPoint);
		}
	}
}

//添加时间自动发送
void UGameProjectInstance::AddCalendar(int Add_Day, int Add_Progress)
{
	DayTime += Add_Day;
	ProgressPoint += Add_Progress;
	CheckOutTime();
}


//成长系统
void UGameProjectInstance::Increase_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA)
{
	Multiplier_Int += Int;
	Multiplier_Ded += Ded;
	Multiplier_Prestige += Prestige;
	Multiplier_Purchasing += Purchasing;
	Multiplier_STA += STA;
}

void UGameProjectInstance::Decrease_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA)
{
	Multiplier_Int -= Int;
	if (Multiplier_Int <= 0)
		Multiplier_Int = 0;
	
	Multiplier_Ded -= Ded;
	if (Multiplier_Ded <= 0)
		Multiplier_Ded = 0;

	Multiplier_Prestige -= Prestige;
	if (Multiplier_Prestige <= 0)
		Multiplier_Prestige = 0;

	Multiplier_Purchasing -= Purchasing;
	if (Multiplier_Purchasing <= 0)
		Multiplier_Purchasing = 0;

	Multiplier_STA -= STA;
	if (Multiplier_STA <= 0)
		Multiplier_STA = 0;
}

void UGameProjectInstance::Time_Extra_Multiplier(float Int, float Ded, float Prestige, float Purchasing, float STA)
{
	Increase_Extra_Multiplier(Int, Ded, Prestige, Purchasing, STA);

	Decrease_Extra_Multiplier(Int, Ded, Prestige, Purchasing, STA);

	//this->OnUpdateDayProgress.__Internal_AddDynamic(this,)
}

float UGameProjectInstance::AddAbility(float BasicValue, float AddValue, const EGrowthData GrowthData)
{
	switch (GrowthData)
	{
	case EGrowthData::None:
		break;
	case EGrowthData::Intelligence:
		return BasicValue+AddValue*Multiplier_Int;
		break;
	case EGrowthData::Dedication:
		return BasicValue + AddValue * Multiplier_Ded;
		break;
	case EGrowthData::Prestige:
		return BasicValue + AddValue * Multiplier_Prestige;
		break;
	case EGrowthData::Purchasing:
		return BasicValue + AddValue * Multiplier_Purchasing;
		break;
	case EGrowthData::Stamina:
		return BasicValue + AddValue * Multiplier_STA;
		break;
	}
	return (BasicValue + AddValue);
}

