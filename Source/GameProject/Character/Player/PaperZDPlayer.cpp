// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PaperZDPlayer.h"
#include "ActorComponent/HealthComp.h"
#include "ActorComponent/HitStopComp.h"
#include "ActorComponent/InputRecorderComp.h"
#include "ActorComponent/SkillComponent.h"
#include "ActorComponent/GethitComp.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Enemy/PaperZDEnemy.h"
#include "GameSetting/PlayerBattleController.h"
#include "GAS/BasicAttributeSet.h"



APaperZDPlayer::APaperZDPlayer()
{
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	HitStopComp = CreateDefaultSubobject<UHitStopComp>(TEXT("HitStopComp"));
	InputRecorder = CreateDefaultSubobject<UInputRecorderComp>(TEXT("InputRecorderComp"));
	GethitComp = CreateDefaultSubobject<UGethitComp>(TEXT("GethitComp"));
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	NowState = ECharacterState::None;

	ATK = 20;
	Critical_Damage = 1;
	Melee_Damage_Increase = 0;
	Ranged_Damage_Increase = 0;
	Critical_Rate = 0.25;
}

void APaperZDPlayer::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	APlayerBattleController* PlayerController = Cast<APlayerBattleController>(GetController());
	PlayerController->ResetKillEnemy();  //重置消灭数量
	InputRecorder->InsertDirectionHistory(EInputDirection::Down);

	HealthComp->BroadDeath.AddDynamic(this, &APaperZDPlayer::OnDeath);

}

void APaperZDPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APaperZDPlayer::Initialize()
{
	//设置属性集
	if (IsValid(AbilitySystem))
	{
		AttributeSet = AbilitySystem->GetSet<UBasicAttributeSet>();
	}
	//给予能力集
	for(const auto& Ability:StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		AbilitySystem->GiveAbility(AbilitySpec);
	}
}


void APaperZDPlayer::OnDeath_Implementation()
{
}

void APaperZDPlayer::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force, const float& Damage,bool bIsCritical)
{
}


EInputDirection APaperZDPlayer::DirectionToTaeget()
{
	if(Target!=nullptr)
	{
		InputRecorder->UpdateDirectionHistory(InputRecorder->GetTargetDirection(Target),true);
		return InputRecorder->VectorToDir(InputRecorder->GetTargetDirection(Target));
	}
	else
	{
		return InputRecorder->GetNowInputDirection();
	}
	
}

FVector2D APaperZDPlayer::VectorToTaeget()
{
    return InputRecorder->DirToVector(DirectionToTaeget());
}

APaperZDEnemy* APaperZDPlayer::LookForEnemy(float MaxDistance, TArray<AActor*> Actors)
{
	float CurrenDistance=MaxDistance;
	APaperZDEnemy* CurrentEnemy=nullptr;
	for (const auto& Enemy : Actors)
	{
		APaperZDEnemy* paperEnemy = Cast<APaperZDEnemy>(Enemy);
		if (paperEnemy!=nullptr)
		{
			float len = FVector::Dist2D(paperEnemy->GetActorLocation(), this->GetActorLocation());
			if (len<=CurrenDistance)
			{
				CurrenDistance = len;
				CurrentEnemy = paperEnemy;
			}
		}
	}
	return CurrentEnemy;
}

void APaperZDPlayer::SphereObjectsReturnResult(FVector Location, float Radius)
{
	TArray<FHitResult> OutHits;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);


	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = false;
	QueryParams.AddIgnoredActor(this);

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);

	GetWorld()->SweepMultiByObjectType(
		OutHits,
		Location,      // Start
		Location,      // End (相同位置表示球体检测)
		FQuat::Identity,    // 旋转
		ObjectQueryParams,  // Object Types
		CollisionShape,     // 球体形状
		QueryParams
	);

	
	for (const auto& Hit : OutHits)
	{
		SpehereHitLoopBody(Hit);
	}
}

void APaperZDPlayer::ReplaceSkillComponent(TSubclassOf<USkillComponent> NewSkill)
{
	if (!NewSkill || !GetWorld())
		return;

	if (SkillComp)
	{
		SkillComp->DestroyComponent();
		SkillComp = nullptr;
	}

	USkillComponent* NewSkillComp = NewObject<USkillComponent>(this, NewSkill);
	if (NewSkillComp)
	{
		NewSkillComp->RegisterComponent();
		SkillComp = NewSkillComp;
	}
}

FDamageStruct APaperZDPlayer::GetCharacterBasicData(EAttackType AttackType)
{
	FDamageStruct Stats;
	Stats.ATK = ATK;
	Stats.CR = Critical_Rate;
	Stats.CD = Critical_Damage;
	switch (AttackType)
	{
	case EAttackType::None:
		Stats.Increase = 0;
		break;
	case EAttackType::Melee:
		Stats.Increase = Melee_Damage_Increase;
		break;
	case EAttackType::Ranged:
		Stats.Increase = Ranged_Damage_Increase;
		break;
	default:
		break;
	}
	return Stats;
}

void APaperZDPlayer::ResetCharacterAttackData(float Extra_ATK, float Extra_Critical, float Extra_Melee, float Extra_Range)
{
	ATK += (Extra_ATK / 100 * ATK);
	Critical_Rate += (Extra_Critical / 200);
	Melee_Damage_Increase += Extra_Melee / 100;
	Ranged_Damage_Increase += Extra_Range / 100;
}

void APaperZDPlayer::GA_Dash(TSubclassOf<UGameplayAbility> GA_Dash)
{
	AbilitySystem->TryActivateAbilityByClass(GA_Dash,true);
}

void APaperZDPlayer::GA_Attack_Melee(TSubclassOf<UGameplayAbility> GA_Attack_Melee)
{
	AbilitySystem->TryActivateAbilityByClass(GA_Attack_Melee, true);
}

void APaperZDPlayer::GA_Attack_Random(TSubclassOf<UGameplayAbility> GA_Attack_Random)
{
	AbilitySystem->TryActivateAbilityByClass(GA_Attack_Random, true);
}

void APaperZDPlayer::GA_QTE(TSubclassOf<UGameplayAbility> GA_QTE)
{
	AbilitySystem->TryActivateAbilityByClass(GA_QTE, true);
}

void APaperZDPlayer::GA_Damage(TSubclassOf<UGameplayAbility> GA_Damage)
{
	AbilitySystem->TryActivateAbilityByClass(GA_Damage, true);
}
