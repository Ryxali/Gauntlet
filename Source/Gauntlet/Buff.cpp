// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Buff.h"
#include "Engine.h"
UBuff::UBuff()
{
	/*AppliesTo_Flags = EBuffAppliesTo::NONE;
	for (EBuffAppliesTo e : AppliesTo)
	{
		AppliesTo_Flags = (EBuffAppliesTo)((uint8)AppliesTo_Flags | (uint8)e);
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("CONSTRUCTIO!")));*/
	
}

UBuff::UBuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP) {
	
}

void UBuff::PostEditChangeProperty(struct FPropertyChangedEvent & PropertyChangedEvent)
{
	AppliesTo_Flags = EBuffAppliesTo::NONE;
	for (auto It(AppliesTo.CreateIterator()); It; It++)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("CON %i"), (uint8)(*It)));
		AppliesTo_Flags = (EBuffAppliesTo)((uint8)AppliesTo_Flags | (uint8)(*It));
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("CONSTRUCTIO2! %i"), (uint8)(AppliesTo[0])));
}

float UBuff::ApplyTo_Implementation(float value)
{
	// Perform no modification by default
	return value;
}

UBuff::~UBuff()
{

}