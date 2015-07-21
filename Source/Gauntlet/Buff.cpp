// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Buff.h"

UBuff::UBuff()
{
}

UBuff::UBuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP) {
}

float UBuff::ApplyTo_Implementation(float value)
{
	// Perform no modification by default
	return value;
}

UBuff::~UBuff()
{

}