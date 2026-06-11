// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "MyClass.h"
#include "Interface/HealthInterface.h"
#include "PaperZDCharacter.h"
#include "PaperZDPlayer.generated.h"

class UHealthComp;
class UHitStopComp;
class UInputRecorderComp;
class UGethitComp;
class USkillComponent;
class UAbilitySystemComponent;
class UGameplayAbility;


UCLASS()
class GAMEPROJECT_API APaperZDPlayer : public APaperZDCharacter,public IHealthInterface ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APaperZDPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;



public:

	virtual void OnDeath_Implementation() override;

	virtual void OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force,const float& Damage,bool bIsCritical);


	UFUNCTION(BlueprintCallable)
	void Initialize();

	//////Function
	//设置碰撞方向；
	UFUNCTION(BlueprintPure)
	EInputDirection DirectionToTaeget();
	//设置攻击方向
	UFUNCTION(BlueprintPure)
	FVector2D VectorToTaeget();
	//寻找敌方目标
	UFUNCTION(BlueprintCallable)
	APaperZDEnemy* LookForEnemy(float MaxDistance, TArray<AActor*>Actors);

	//球体碰撞
	UFUNCTION(BlueprintCallable)
	void SphereObjectsReturnResult(FVector Location, float Radius);
	UFUNCTION(BlueprintImplementableEvent)
	void SpehereHitLoopBody(FHitResult HitResult);

	////Property	
	//角色状态设置
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterState NowState;

	//根据数值进行设定
	UFUNCTION(BlueprintImplementableEvent, Category = "State")
	void Set_Basic_Data();

	

	UPROPERTY(BlueprintReadWrite, Category = "Move")
	bool IsAbleMevement=true;

	UPROPERTY(BlueprintReadWrite, Category = "Move")
	bool IsAbleJump = true;

	UPROPERTY(BlueprintReadWrite, Category = "Move")
	bool IsAbleAttack = true;

	UPROPERTY(BlueprintReadWrite, Category = "Target")
	AActor* Target;

	//摄像机效果设置



	//技能组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot", meta = (AllowPrivateAccess = "true"))
	class USkillComponent* SkillComp;
	//更换技能组件
	UFUNCTION(BlueprintCallable, Category = "Slot")
	void ReplaceSkillComponent(TSubclassOf<USkillComponent> NewSkill);


	//角色固定组件
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	class UHitStopComp* HitStopComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InputRecoder", meta = (AllowPrivateAccess = "true"))
	class UInputRecorderComp*InputRecorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GetHit", meta = (AllowPrivateAccess = "true"))
	class UGethitComp* GethitComp;
	

	//角色攻击数据
public:
	//物理增伤
	UPROPERTY(BlueprintReadWrite)
	float Melee_Damage_Increase;

	//远程增伤
	UPROPERTY(BlueprintReadWrite)
	float  Ranged_Damage_Increase;

	UPROPERTY(BlueprintReadWrite)
	float  ATK;

	
	UPROPERTY(BlueprintReadWrite)
	float Critical_Rate;

	UPROPERTY(BlueprintReadWrite)
	float Critical_Damage;

	UFUNCTION(BlueprintPure)
	FDamageStruct GetCharacterBasicData(EAttackType AttackType);

	//获取角色数据并重新设置
	UFUNCTION(BlueprintCallable)
	void ResetCharacterAttackData(float Extra_ATK,float Extra_Critical,float Extra_Melee,float Extra_Range);

	//GAS
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}
	//属性集
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UBasicAttributeSet* AttributeSet;

	//能力集
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GA_Dash(TSubclassOf<UGameplayAbility> GA_Dash);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GA_Attack_Melee(TSubclassOf<UGameplayAbility> GA_Attack_Melee);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GA_Attack_Random(TSubclassOf<UGameplayAbility> GA_Attack_Random);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GA_QTE(TSubclassOf<UGameplayAbility> GA_QTE);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GA_Damage(TSubclassOf<UGameplayAbility> GA_Damage);

};


