// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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
};
