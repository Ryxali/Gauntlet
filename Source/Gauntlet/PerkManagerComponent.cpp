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
	// ...
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("dassaddas"));
	for (auto It(Perks.CreateIterator()); It; It++) {
		if (!(*It)) return;
		if (!(*It)->IsValidLowLevel()) return;

		(*It)->ConditionalBeginDestroy(); //instantly clears UObject out of memory
		(*It) = nullptr;
	}
}


// Called every frame
void UPerkManagerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...not
}

void UPerkManagerComponent::IncrementCombo()
{
	InternalComboCount++;
	
	/*while (ComboIterator != NULL && ComboIterator->Self->RequiredCombo <= InternalComboCount)
	{
		ComboIterator->Self->Apply();
		ComboIterator = ComboIterator->Next; // Might be NULL
	}*/
	/*auto it = Perks.CreateIterator();
	while (it != Perks.Last)
	{
		//Perks[it.GetIndex()]
	}*/

	for (auto It(Perks.CreateIterator()); It; It++) {
		if (!(*It)->IsValidLowLevel()) continue;
		// ((
		if ((*It)->RequiredCombo == InternalComboCount)
		{
			
		}
		if (
			(*It)->Repeating
			&& (InternalComboCount >= (*It)->RequiredCombo)
			&& ((*It)->ComboPeriod == 0 || FMath::Floor(FMath::Fmod(InternalComboCount, (*It)->ComboPeriod)) == 0)) // && (InternalComboCount % ((*It)->ComboPeriod))
		{
			(*It)->Apply();
		}

	}
	
	/*for (int32 i = 0; i < Perks.Num(); i++)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), i));
		if ((Perks[i]->RequiredCombo == 0 || InternalComboCount <= Perks[i]->RequiredCombo) && InternalComboCount % Perks[i]->ComboPeriod == 0)
		{
			
			Perks[i]->Apply();
		}
		
	}*/
	
}

void UPerkManagerComponent::ResetCombo()
{
	InternalComboCount = 0;
}

void UPerkManagerComponent::AddPerk(TSubclassOf<UPerk> Perk)
{
	
	UPerk* p = Cast<UPerk>( StaticConstructObject(Perk));
	//PerkNode* pn = new PerkNode(p);

	// The Perk must NOT be removed by garbage collection!
	p->SetFlags(RF_RootSet);
	
	Perks.Add(p);
	//Root = pn;
	/*if (Root != NULL)
	{
		PerkNode* Iterator = Root;
		while (Iterator->HasNext()) {
			if (Iterator->Self->RequiredCombo > p->RequiredCombo) {
				PerkNode* Next = Iterator->Next;
				Iterator->Next = pn;
				pn->Next = Next;
				break;
			}
		}
	} 
	else
	{
		Root = pn;
		ComboIterator = Root;
	}*/
	
	// Duo list - one for one-time and one for repeated, where the repeated are inserted from one-time
	//p->Apply();
	//UClass::GetDefaultObject<UPerk>();
	///Perk->GetDefaultObject()->
}