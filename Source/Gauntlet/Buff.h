// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BuffAppliesToEnum.h"
#include "Object.h"
#include "Buff.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class GAUNTLET_API UBuff : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UBuff();
	~UBuff();

	// Enables us to spawn actors
	virtual UWorld* GetWorld() const override;
	// Called from the manager to enable actor spawning
	void SetWorld(UWorld* World);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	float ApplyTo(float BaseValue, float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Buff")
	void OnHit(AActor* HitActor);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent & PropertyChangedEvent);

	/* 
		Orders the buff to calculate it's end time, allowing its manager to know
		when it should be destroyed.
	*/
	UFUNCTION()
	void StartDecay(float StartTime);

	// The varius kinds of values this buff applies to.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	TArray<EBuffAppliesTo> AppliesTo;

	// Compressed bitset form of AppliesTo
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Buff")
	EBuffAppliesTo AppliesTo_Flags;

	/*
		Whether multiple buffs of this class can be applied to the same actor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool IsUnique;

	/*
		Whether we should refresh the life time of buffs of this time
		already present on the actor when adding a new one.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool RefreshDuplicatesOnAdd;

	// Whether this buff should be cleansed by managers.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool CanBeCleansed;

	// How long time (in seconds) this buff should be active until destroyed.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	float LifeTime;

	// The time this Buff should be counted as decayed
	UPROPERTY()
	float EndTime;

	UPROPERTY(BlueprintReadOnly, Category = "Buff")
	AActor* Host;

private:
	UWorld* World;
};
