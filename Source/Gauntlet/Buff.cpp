// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Buff.h"
#include "Engine.h"
UBuff::UBuff()
{
	//EndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + LifeTime;
}

UBuff::UBuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP) {
	//EndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + LifeTime;
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

void UBuff::Initialize()
{
	EndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + LifeTime;
}

float UBuff::ApplyTo_Implementation(float value)
{
	// Perform no modification by default
	return value;
}

UBuff::~UBuff()
{

}