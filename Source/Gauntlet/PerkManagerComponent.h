// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Perk.h"
class UPerk;
class AActor;

#include "Components/ActorComponent.h"
#include "PerkManagerComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UPerkManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPerkManagerComponent();
	~UPerkManagerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Increment the Combo counter, applying any perks relevant for that combo value
	UFUNCTION(BlueprintCallable, Category = "Combo")
	void IncrementCombo(AActor* EnemyHit);

	// Reset the combo counter to 0, resetting any perks in the process
	UFUNCTION(BlueprintCallable, Category = "Combo")
	void ResetCombo();

	// Add a new perk, allowing it to be applied as the player progresses through combos
	UFUNCTION(BlueprintCallable, Category = "Combo")
	void AddPerk(TSubclassOf<UPerk> Perk);

	// Get the current combo count
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combo")
	int32 GetComboCount() const;

private:
	UPROPERTY()
	int32 InternalComboCount;
	UPROPERTY()
	TArray<UPerk*> Perks;
};
