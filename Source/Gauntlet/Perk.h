// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class AActor;
#include "Object.h"
#include "Perk.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class GAUNTLET_API UPerk : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPerk();

	UFUNCTION(BlueprintImplementableEvent, Category = "Perk")
	void Apply(AActor* EnemyHit, AGameMode* GameMode, AGameState* GameState, ACharacter* Player);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Perk")
	/** How much combo is required until this perk is applied */
	int32 RequiredCombo;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Perk")
	/** Should this perk be applied every ComboPeriod? */
	bool Repeating;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Perk")
	/** If we're repeating, how many combos to wait until repeating again */
	int32 ComboPeriod;
private:
	
};
