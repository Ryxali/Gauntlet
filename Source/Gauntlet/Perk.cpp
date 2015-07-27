// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
//#include "Runtime\Engine\Classes\Engine\Level.h"
#include "BuffManagerComponent.h"
#include "Perk.h"


UPerk::UPerk()
{
	RequiredCombo = 0;
	Repeating = false;
	ComboPeriod = 0;
	World = NULL;
}

UPerk::UPerk(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP) {
	RequiredCombo = 0;
	Repeating = false;
	ComboPeriod = 0;
	World = NULL;
}

void UPerk::SetWorld(UWorld* World)
{
	this->World = World;
}

UWorld* UPerk::GetWorld() const
{
	return World;
}

void UPerk::AddBuffTo(AActor* Target, TSubclassOf<UBuff> Buff, EPerkOperationResult& Branches)
{
	Branches = EPerkOperationResult::Failed;
	UBuffManagerComponent* Temp = Cast<UBuffManagerComponent>(Target->FindComponentByClass(UBuffManagerComponent::StaticClass()));
	if (Temp != NULL)
	{
		Temp->AddBuff(Buff);
		Branches = EPerkOperationResult::Success;
	}
}