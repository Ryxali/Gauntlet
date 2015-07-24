// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Buff.h"
#include "Engine.h"
UBuff::UBuff()
{
	CanBeCleansed = true;
}

UBuff::UBuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP) {
	CanBeCleansed = true;
}

void UBuff::PostEditChangeProperty(struct FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	AppliesTo_Flags = EBuffAppliesTo::NONE;
	for (auto It(AppliesTo.CreateIterator()); It; It++)
	{
		AppliesTo_Flags = (EBuffAppliesTo)((uint8)AppliesTo_Flags | (uint8)(*It));
	}
	
}

void UBuff::StartDecay(float StartTime)
{
	EndTime = StartTime + LifeTime;
}

float UBuff::ApplyTo_Implementation(float BaseValue, float Value)
{
	// Perform no modification by default
	return Value;
}

UBuff::~UBuff()
{

}