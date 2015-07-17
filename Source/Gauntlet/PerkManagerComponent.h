// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Perk.h"
class UPerk;

#include "Components/ActorComponent.h"
#include "PerkManagerComponent.generated.h"


struct PerkNode
{
	UPerk* Self;
	PerkNode* Next;

	inline PerkNode(UPerk* Self)
	{
		this->Self = Self;
		this->Next = NULL;
	}
	

	inline bool HasNext() const
	{
		return Next != NULL;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UPerkManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPerkManagerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "Combo")
	void IncrementCombo();

	UFUNCTION(BlueprintCallable, Category = "Combo")
	void ResetCombo();

	UFUNCTION(BlueprintCallable, Category = "Combo")
	void AddPerk(TSubclassOf<UPerk> Perk);

private:
	UPROPERTY()
	int32 InternalComboCount;
	UPROPERTY()
	TArray<UPerk*> Perks;
};
