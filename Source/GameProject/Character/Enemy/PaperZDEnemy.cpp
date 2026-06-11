// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/PaperZDEnemy.h"
#include "ActorComponent/HealthComp.h"
#include "ActorComponent/InputRecorderComp.h"
#include "ActorComponent/GethitComp.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Player/PaperZDPlayer.h"
#include "Function/MyBlueprintFunctionLibrary.h"
#include "GAS/BasicAttributeSet.h"





APaperZDEnemy::APaperZDEnemy()
{
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	InputRecorderComp = CreateDefaultSubobject<UInputRecorderComp>(TEXT("InputRecorderComp"));
	GethitComp = CreateDefaultSubobject<UGethitComp>(TEXT("GethitComp"));
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

void APaperZDEnemy::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
	HealthComp->BroadDeath.AddDynamic(this,&APaperZDEnemy::OnDeath);
}

void APaperZDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UMyBlueprintFunctionLibrary::ActorToCamera(this);
}


void APaperZDEnemy::Initialize()
{
	//设置属性集
	if (IsValid(AbilitySystemComp))
	{
		AttributeSet = AbilitySystemComp->GetSet<UBasicAttributeSet>();
	}
	//给予能力集
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		AbilitySystemComp->GiveAbility(AbilitySpec);
	}

	//设置Target
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->GetPawn())
	{
		APaperZDPlayer* PlayerCharacter = Cast<APaperZDPlayer>(PC->GetPawn());
		Target = PlayerCharacter;
	}
}

void APaperZDEnemy::OnDeath_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("怪物死亡"));
	this-> Destroy();
}

void APaperZDEnemy::OnDmg_Implementation(const FHitResult& HitResult, const FVector& AttackVec, const float& Force, const float& Damage,bool bIsCritical)
{
}
