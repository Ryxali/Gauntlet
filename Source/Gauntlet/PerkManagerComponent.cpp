// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "PerkManagerComponent.h"
#include "Perk.h"
#include "Engine.h"
// Sets default values for this component's properties
UPerkManagerComponent::UPerkManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	InternalComboCount = 0;
	//Root = NULL;
	//ComboIterator = NULL;
	Perks = TArray<UPerk*>();
}


// Called when the game starts
void UPerkManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPerkManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

UPerkManagerComponent::~UPerkManagerComponent()
{
}


// Called every frame (Disabled by default)
void UPerkManagerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// 
}

void UPerkManagerComponent::IncrementCombo(AActor* EnemyHit)
{
	InternalComboCount++;
	for (auto It(Perks.CreateIterator()); It; It++) {
		if (!(*It)->IsValidLowLevel()) continue;

		if ((*It)->RequiredCombo == InternalComboCount)
		{
			(*It)->Apply(EnemyHit, UGameplayStatics::GetGameMode(this), UGameplayStatics::GetGameState(this), UGameplayStatics::GetPlayerCharacter(this, 0));
			continue;
		}

		if ((*It)->Repeating
			&& (InternalComboCount >= (*It)->RequiredCombo)
			&& ((*It)->ComboPeriod == 0 || FMath::Floor(FMath::Fmod(InternalComboCount, (*It)->ComboPeriod)) == 0)) // && (InternalComboCount % ((*It)->ComboPeriod))
		{
			(*It)->Apply(EnemyHit, UGameplayStatics::GetGameMode(this), UGameplayStatics::GetGameState(this), UGameplayStatics::GetPlayerCharacter(this, 0));
		}

	}
	
}

void UPerkManagerComponent::ResetCombo()
{
	InternalComboCount = 0;
}

void UPerkManagerComponent::AddPerk(TSubclassOf<UPerk> Perk)
{
	if (Perk == NULL) return;
	UPerk* p = NewObject<UPerk>((UObject*)GetTransientPackage(), Perk);
	p->SetWorld(GetWorld());
	Perks.Add(p);
}

bool UPerkManagerComponent::hasPerk(TSubclassOf<UPerk> PerkType) const
{
	for (UPerk* Perk : Perks)
	{
		if (Perk->IsValidLowLevel() && Perk->GetClass() == PerkType) return true;
	}
	return false;
}

int32 UPerkManagerComponent::GetComboCount() const
{
	return InternalComboCount;
}