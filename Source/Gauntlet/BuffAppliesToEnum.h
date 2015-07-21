// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EBuffAppliesTo : uint8 {
	NONE = 0x0	UMETA(Hidden),
	GOLD_DROP_QUANTITY = 0x1	UMETA(DisplayName = "Gold Drop Quantity"),

	ALL = 0x3	UMETA(Hidden)
};

inline EBuffAppliesTo operator|(const EBuffAppliesTo& a, const EBuffAppliesTo& b)
{
	return (EBuffAppliesTo)((uint8)a | (uint8)b);
}

inline EBuffAppliesTo operator&(const EBuffAppliesTo& a, const EBuffAppliesTo& b)
{
	return (EBuffAppliesTo)((uint8)a & (uint8)b);
}

