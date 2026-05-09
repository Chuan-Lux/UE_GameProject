// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyClass.h"
#include "InputRecorderComp.generated.h"


USTRUCT(BlueprintType)
struct FInputDirectionHistory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionData")
	EInputDirection Dir = EInputDirection::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionData")
	float Time = 0.0f;

	FInputDirectionHistory() = default;
	FInputDirectionHistory(EInputDirection InDir, float InTime) : Dir(InDir), Time(InTime) {}

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UInputRecorderComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputRecorderComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//记录历史输入
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	TArray<FInputDirectionHistory> DirectionHistory;

	UFUNCTION(BlueprintCallable)
	void UpdateDirectionHistory(FVector2D InputMovement,bool IsEight);

	UFUNCTION(BlueprintCallable)
	void UpdateDirectionHistory8(FVector2D InputMovement);

	UFUNCTION(BlueprintCallable)
	void UpdateDirectionHistory4(FVector2D InputMovement);

	//获得目标相对方向
	UFUNCTION(BlueprintPure)
	FVector2D GetTargetDirection(AActor*target);

	UFUNCTION(BlueprintCallable)
	void InsertDirectionHistory(EInputDirection Dir);

	UFUNCTION(BlueprintPure)
	EInputDirection GetNowInputDirection();

	UFUNCTION(BlueprintPure)
	FVector2D GetNowInputVector();

	//转换
	UFUNCTION(BlueprintPure)
	EInputDirection VectorToDir(FVector2D vector);

	UFUNCTION(BlueprintPure)
	EInputDirection VectorToDir4(FVector2D vector);


	//转换
	UFUNCTION(BlueprintPure)
	FVector2D DirToVector(EInputDirection Dir);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
