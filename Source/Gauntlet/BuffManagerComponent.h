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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddBuff(TSubclassOf<UBuff> Buff);

	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddValue(FName Name, float Value, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags);
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetValue(FName Name, float Value);
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetFlags(FName Name, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags);

	UFUNCTION(BlueprintCallable, Category = "Buff")
	float GetValue(FName Name);
private:
	UPROPERTY()
	TArray<UBuff*> Buffs;

	UFUNCTION()
	EBuffAppliesTo ToSingleEnum(const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags) const;

	UFUNCTION()
	bool HasFlag(const UBuff* Buff, const EBuffAppliesTo& Flag) const;

	UPROPERTY()
	TMap<FName, FBuffableValue> Values;


};
