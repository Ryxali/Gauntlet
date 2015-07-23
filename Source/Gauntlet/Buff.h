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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	float ApplyTo(float value);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent & PropertyChangedEvent) override;

	/* 
		Orders the buff to calculate it's end time, allowing any manager to know
		when it should be destroyed.
	*/
	UFUNCTION()
	void StartDecay(float StartTime);

	// The varius kinds of values this buff applies to.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	TArray<EBuffAppliesTo> AppliesTo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Buff")
	EBuffAppliesTo AppliesTo_Flags;

	/*
		Whether multiple buffs of this class can be applied to the same actor.
		If true, applying a new buff will instead cause the decay to restart.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool IsUnique;

	// Whether this buff should be cleansed by managers.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool CanBeCleansed;

	// How long time (in seconds) this buff should be active until destroyed.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	float LifeTime;

	UPROPERTY()
	float EndTime;

	
};
