// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/*
	Defines the various flags used to identifiy buffs.
*/
UENUM(BlueprintType)
enum class EBuffAppliesTo : uint8 {
	NONE = 0x0	UMETA(Hidden),
	GOLD_DROP_QUANTITY		= 0x1	UMETA(DisplayName = "Gold Drop Quantity"),
	ATTACK_SPEED			= 0x2	UMETA(DisplayName = "Attack Speed"),
	PLAYER_SHIELD_ACTIVE	= 0x4	UMETA(DisplayName = "Player shield activated"),
	BLINK_COOLDOWN_DURATION = 0x8	UMETA(DisplayName = "Blink Cooldown Duration"),
	ALL = 0xf	UMETA(Hidden)
};

inline EBuffAppliesTo operator|(const EBuffAppliesTo& a, const EBuffAppliesTo& b)
{
	return (EBuffAppliesTo)((uint8)a | (uint8)b);
}

inline EBuffAppliesTo operator&(const EBuffAppliesTo& a, const EBuffAppliesTo& b)
{
	return (EBuffAppliesTo)((uint8)a & (uint8)b);
}

