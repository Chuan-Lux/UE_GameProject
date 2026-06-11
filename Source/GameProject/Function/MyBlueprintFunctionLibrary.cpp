// Fill out your copyright notice in the Description page of Project Settings.


#include "Function/MyBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Notify/EffectNotify.h"
#include "PaperFlipbookComponent.h"  



void UMyBlueprintFunctionLibrary::TickRotation(APaperCharacter* Character)
{
	if (!Character->GetCharacterMovement())
	{
		return;
	}

	FVector WorldSpeed = Character-> GetCharacterMovement()->Velocity;
	FVector LocalVelocity = Character->GetTransform().InverseTransformVector(WorldSpeed);
	float CurrentSpeedX = LocalVelocity.X;

	FRotator TargetRotation;
	float TargetScale;
	FVector SpriteScale;

	FVector NowScale = Character->GetSprite()->GetComponentScale();
	SpriteScale = NowScale;
	SpriteScale.X = FMath::Abs(NowScale.X);

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

	//Character->GetSprite()->SetWorldRotation(TargetRotation);
	Character->GetSprite()->SetWorldScale3D(FVector(TargetScale* SpriteScale.X, SpriteScale.Y, SpriteScale.Z));
}

FVector UMyBlueprintFunctionLibrary::Vector_WorldCastToLocal(AActor* Target, FVector WorldVector)
{
	if (Target == nullptr)
	{
		return FVector(0, 0, 0);
	}
	FRotator ActorWorldRotation = Target->GetActorRotation();
	FVector LocalVector = ActorWorldRotation.GetInverse().RotateVector(WorldVector);
	return LocalVector;
}

FVector UMyBlueprintFunctionLibrary::Vector_LocalCastToWorld(AActor* Target, FVector LocalVector)
{
	if (Target == nullptr)
	{
		return FVector(0, 0, 0);
	}
	return Target->GetActorRotation().RotateVector(LocalVector);
}

void UMyBlueprintFunctionLibrary::WidgetToCamera(USceneComponent* Widget)
{
	if (Widget == nullptr)
	{
		return;
	}
	//获得玩家相机场景组件
	APlayerCameraManager* CameraManager = Widget->GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	USceneComponent* CameraSceneComponent = CameraManager->GetTransformComponent();
	if (CameraSceneComponent == nullptr)
	{
		return;
	}

	FVector WidgetLocation = Widget->GetComponentLocation();
	FVector PlayerCamera = CameraSceneComponent->GetComponentLocation();

	FVector Direction = PlayerCamera - WidgetLocation;
	FRotator NewRotation = Direction.Rotation();
	Widget->SetWorldRotation(NewRotation);
}

void UMyBlueprintFunctionLibrary::ActorToCamera(AActor* Source)
{
	if (!Source)
		return;

	//获得玩家相机场景组件
	APlayerCameraManager* CameraManager = Source->GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	USceneComponent* CameraSceneComponent = CameraManager->GetTransformComponent();
	if (CameraSceneComponent == nullptr)
	{
		return;
	}

	FVector SourceLocation = Source->GetActorLocation();
	FVector PlayerCamera = CameraSceneComponent->GetComponentLocation();

	FVector Direction = PlayerCamera -SourceLocation;
	FRotator NewRotation = Direction.Rotation();

	NewRotation.Yaw -= 90.0f;
	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;

	Source->SetActorRotation(NewRotation);
}




float UMyBlueprintFunctionLibrary::DamageCalculation(const float ATK, const float Increase, const float Critical_Rate, const float Critical_Damage, bool& bIsCritical)
{
	float RandomValue = FMath::FRand();
	bIsCritical= RandomValue <= Critical_Rate;
	float Critical = 1;
	if (bIsCritical)
	{
		Critical = 1 + Critical_Damage;
	}
	float damage = ATK * (1 + Increase) * Critical;
	return damage;
}

bool UMyBlueprintFunctionLibrary::Probability(float Prob)
{
	float RandomValue = FMath::FRand();
	bool bIsTrigger = RandomValue <= Prob;
	return bIsTrigger;
}

void UMyBlueprintFunctionLibrary::ExcuteNotify(const UObject* WorldContextObject, TSubclassOf<UEffectNotify> NotifyClass)
{
	if (NotifyClass && WorldContextObject)
	{
		UWorld* World = WorldContextObject->GetWorld();
		if (World)
		{
			// 使用 World 作为 Outer，对象随 World 生命周期管理
			UEffectNotify* Notify = NewObject<UEffectNotify>(World, NotifyClass);
			if (Notify)
			{
				Notify->NotifyBegin();
				Notify->MarkAsGarbage();
			}
		}
	}
}

TArray<FIndexNum> UMyBlueprintFunctionLibrary::InsertData(TArray<FIndexNum> List, int Index, int num)
{
	bool bFound = false;
	int length = List.Num();

	for (int i = 0; i < length; i++)
	{
		if (List[i].Index == Index)
		{
			List[i].Num += num;
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		FIndexNum NewItem;
		NewItem.Index = Index;
		NewItem.Num = num;
		List.Add(NewItem);
	}

	return List;
}

TArray<FIndexNum> UMyBlueprintFunctionLibrary::RemoveData(TArray<FIndexNum> List, int Index, int num)
{
	int length = List.Num();

	for (int i = 0; i < length; i++)
	{
		if (List[i].Index == Index)
		{
			List[i].Num -= num;
			if (List[i].Num <= 0)
			{
				List.RemoveAt(i);
			}
			break;
		}
	}
	return List;
}




