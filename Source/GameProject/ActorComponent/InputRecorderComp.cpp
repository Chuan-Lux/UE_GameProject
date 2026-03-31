// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InputRecorderComp.h"
#include "Function/MyBlueprintFunctionLibrary.h"



// Sets default values for this component's properties
UInputRecorderComp::UInputRecorderComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputRecorderComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInputRecorderComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UInputRecorderComp::UpdateDirectionHistory(FVector2D InputMovement)
{
	
	if (InputMovement.X != 0.f || InputMovement.Y != 0.f)
	{
		// 先归一化输入向量，确保方向判断准确
		FVector2D NormalizedInput = InputMovement.GetSafeNormal();

		// 计算角度（弧度转角度）
		float Angle = FMath::RadiansToDegrees(FMath::Atan2(NormalizedInput.Y, NormalizedInput.X));

		// 将角度映射到 0-360 度范围
		if (Angle < 0)
		{
			Angle += 360.0f;
		}

		// 根据角度判断8方向
		// 将360度分为8个区间，每个区间45度
		if (Angle >= 337.5f || Angle < 22.5f)
		{
			InsertDirectionHistory(EInputDirection::Right);      // 0度
		}
		else if (Angle >= 22.5f && Angle < 67.5f)
		{
			InsertDirectionHistory(EInputDirection::Up_Right);   // 45度
		}
		else if (Angle >= 67.5f && Angle < 112.5f)
		{
			InsertDirectionHistory(EInputDirection::Up);         // 90度
		}
		else if (Angle >= 112.5f && Angle < 157.5f)
		{
			InsertDirectionHistory(EInputDirection::Up_Left);    // 135度
		}
		else if (Angle >= 157.5f && Angle < 202.5f)
		{
			InsertDirectionHistory(EInputDirection::Left);       // 180度
		}
		else if (Angle >= 202.5f && Angle < 247.5f)
		{
			InsertDirectionHistory(EInputDirection::Down_Left);  // 225度
		}
		else if (Angle >= 247.5f && Angle < 292.5f)
		{
			InsertDirectionHistory(EInputDirection::Down);       // 270度
		}
		else if (Angle >= 292.5f && Angle < 337.5f)
		{
			InsertDirectionHistory(EInputDirection::Down_Right); // 315度
		}
	}

	// 保持只记录4个数据
	if (DirectionHistory.Num() > 4)
	{
		DirectionHistory.SetNum(4);
	}
}

FVector2D UInputRecorderComp::GetTargetDirection(AActor* target)
{
	if (target==nullptr)
	{
		return FVector2D::ZeroVector;
	}
	FVector Dir = FVector(target->GetActorLocation() - GetOwner()->GetActorLocation());
	FVector local= UMyBlueprintFunctionLibrary::Vector_WorldCastToLocal(GetOwner(),Dir.GetSafeNormal());
	FVector2D dir= FVector2D(local.X,-local.Y);
	return dir.GetSafeNormal();
}

void UInputRecorderComp::InsertDirectionHistory(EInputDirection Dir)
{
	if (DirectionHistory.Num() == 0)
	{
		DirectionHistory.Add(FInputDirectionHistory(Dir, 1));  // 第一次添加，时间设为1
		return;
	}
	if (DirectionHistory[0].Dir != Dir)
	{
		DirectionHistory.Insert((FInputDirectionHistory(Dir, 0)), 0);
	}
	else
	{
		DirectionHistory[0].Time += 1;
	}
}

EInputDirection UInputRecorderComp::GetNowInputDirection()
{

	if (DirectionHistory.Num() <= 0)
	{
		return EInputDirection::None;
	}
	else
	{
		EInputDirection Now_Dir = DirectionHistory[0].Dir;
		return Now_Dir;
	}
}

FVector2D UInputRecorderComp::GetNowInputVector()
{
	EInputDirection dir=GetNowInputDirection();
	return DirToVector(dir);
}

EInputDirection UInputRecorderComp::VectorToDir(FVector2D vector)
{

	FVector2D InputMovement = vector;
	if (InputMovement.X != 0.f || InputMovement.Y != 0.f)
	{
		FVector2D NormalizedInput = InputMovement.GetSafeNormal();
		float Angle = FMath::RadiansToDegrees(FMath::Atan2(NormalizedInput.Y, NormalizedInput.X));
		if (Angle < 0)
		{
			Angle += 360.0f;
		}
		if (Angle >= 337.5f || Angle < 22.5f)
		{
			return EInputDirection::Right;      // 0度
		}
		else if (Angle >= 22.5f && Angle < 67.5f)
		{
		    return EInputDirection::Up_Right;   // 45度
		}
		else if (Angle >= 67.5f && Angle < 112.5f)
		{
			return EInputDirection::Up;         // 90度
		}
		else if (Angle >= 112.5f && Angle < 157.5f)
		{
			return EInputDirection::Up_Left;    // 135度
		}
		else if (Angle >= 157.5f && Angle < 202.5f)
		{
			return EInputDirection::Left;       // 180度
		}
		else if (Angle >= 202.5f && Angle < 247.5f)
		{
			return EInputDirection::Down_Left;  // 225度
		}
		else if (Angle >= 247.5f && Angle < 292.5f)
		{
			return EInputDirection::Down;       // 270度
		}
		else if (Angle >= 292.5f && Angle < 337.5f)
		{
			return EInputDirection::Down_Right; // 315度
		}
		return EInputDirection::Center;
	}
	else
	{
		return EInputDirection::Center;
	}
}

FVector2D UInputRecorderComp::DirToVector(EInputDirection Dir)
{
	switch (Dir)
	{
	case EInputDirection::None:
		break;
	case EInputDirection::Center:
		break;
	case EInputDirection::Up:
		return FVector2D(0, 1);
		break;
	case EInputDirection::Down:
		return FVector2D(0, -1);
		break;
	case EInputDirection::Right:
		return FVector2D(1, 0);
		break;
	case EInputDirection::Left:
		return FVector2D(-1, 0);
		break;
	case EInputDirection::Up_Left:
		return FVector2D(-0.70710678f, 0.70710678f);
		break;
	case EInputDirection::Up_Right:
		return FVector2D(0.70710678f, 0.70710678f);
		break;
	case EInputDirection::Down_Left:
		return FVector2D(-0.70710678f, -0.70710678f);
		break;
	case EInputDirection::Down_Right:
		return FVector2D(0.70710678f, -0.70710678f);
		break;
	}
	return FVector2D(0, 0);
}

