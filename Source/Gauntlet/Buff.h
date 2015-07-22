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

	//virtual void PostInitProperties() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	float ApplyTo(float value);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent & PropertyChangedEvent) override;

	virtual void Initialize();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	TArray<EBuffAppliesTo> AppliesTo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Buff")
	EBuffAppliesTo AppliesTo_Flags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	float LifeTime;

	UPROPERTY()
	float EndTime;
};
