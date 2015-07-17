// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "Perk.h"


UPerk::UPerk()
{
	RequiredCombo = 0;
	Repeating = false;
	ComboPeriod = 0;
}

UPerk::UPerk(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP) {
	RequiredCombo = 0;
	Repeating = false;
	ComboPeriod = 0;
}

