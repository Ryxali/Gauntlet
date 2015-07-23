// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Buff.h"
#include "BuffAppliesToEnum.h"
#include "Components/ActorComponent.h"
#include "BuffManagerComponent.generated.h"

USTRUCT()
struct FBuffableValue
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	float Value;
	UPROPERTY()
	EBuffAppliesTo AppliesTo_Flags;

	FBuffableValue(float Value = 0.0f, EBuffAppliesTo AppliesTo_Flags = EBuffAppliesTo::NONE) : Value(Value), AppliesTo_Flags(AppliesTo_Flags)
	{
	}
};

/*
	The Buff Manager Component is responsible for storing
	buffs and values, applying the buff modification to values
	upon retreival, and clearing buffs when appropriate.
*/
UCLASS( ClassGroup=(Buff), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UBuffManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffManagerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Adds a new buff to this component and by extension - the actor it's a component of
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddBuff(TSubclassOf<UBuff> Buff);

	// Adds a new buffable value to this component
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddValue(FName Name, float Value, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags);
	// Set a value in this component.
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetValue(FName Name, float Value);
	// Set the flags a value in this component applies to
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetFlags(FName Name, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags);

	// Get a value in this component, applying any relevant buffs to it in the process
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Buff")
	float GetValue(FName Name) const;

	// Clear this components of all clearable buffs
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void CleanseBuffs();
private:
	UPROPERTY()
	TArray<UBuff*> Buffs;

	// Helper function to turn an array of flags into a single value
	UFUNCTION()
	EBuffAppliesTo ToSingleEnum(const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags) const;

	// Helper function to determine if the buff has any of the provided flags
	UFUNCTION()
	bool HasFlag(const UBuff* Buff, const EBuffAppliesTo& Flag) const;

	UPROPERTY()
	TMap<FName, FBuffableValue> Values;


};
