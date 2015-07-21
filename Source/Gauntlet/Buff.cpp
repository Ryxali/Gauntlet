// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Buff.h"

UBuff::UBuff()
{
	AppliesTo_Flags = EBuffAppliesTo::NONE;
	for (EBuffAppliesTo e : AppliesTo)
	{
		AppliesTo_Flags = (EBuffAppliesTo)((uint8)AppliesTo_Flags | (uint8)e);
	}

	
}

UBuff::UBuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP) {
	AppliesTo_Flags = EBuffAppliesTo::NONE;
	for (EBuffAppliesTo e : AppliesTo)
	{
		AppliesTo_Flags = (EBuffAppliesTo)((uint8)AppliesTo_Flags | (uint8)e);
	}
}

float UBuff::ApplyTo_Implementation(float value)
{
	// Perform no modification by default
	return value;
}

UBuff::~UBuff()
{

}