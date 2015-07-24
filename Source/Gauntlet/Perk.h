// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class AActor;
#include "Object.h"

#include "Perk.generated.h"

UENUM(BlueprintType)
enum class EPerkOperationResult : uint8
{
	Success,
	Failed
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class GAUNTLET_API UPerk : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPerk();

	// Called when the effects of this perk should be executed
	UFUNCTION(BlueprintImplementableEvent, Category = "Perk")
	void Apply(AActor* EnemyHit, AGameMode* GameMode, AGameState* GameState, ACharacter* Player);

	/*UFUNCTION(BlueprintCallable, Category = "Perk")
	void SpawnActor(); //AActor* EnemyHit, AGameMode* GameMode, AGameState* GameState, ACharacter* Player
	*/
	//ULevel* GetLevel() const;
	virtual UWorld* GetWorld() const override;

	void SetWorld(UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "Buff", Meta = (ExpandEnumAsExecs = "Branches"))
	void AddBuffTo(AActor* Target, TSubclassOf<UBuff> Buff, EPerkOperationResult& Branches);

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
	UWorld* World;
};
