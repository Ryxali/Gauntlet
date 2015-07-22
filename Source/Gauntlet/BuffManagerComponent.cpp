// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "BuffManagerComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UBuffManagerComponent::UBuffManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuffManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffManagerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}



void UBuffManagerComponent::AddBuff(TSubclassOf<UBuff> Buff)
{
	UBuff* p = NewObject<UBuff>((UObject*)GetTransientPackage(), Buff);
	Buffs.Add(p);
}

void UBuffManagerComponent::AddValue(FName Name, float Value, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags)
{
	Values.Add(Name, FBuffableValue(Value, ToSingleEnum(Flags)));
}

void UBuffManagerComponent::SetValue(FName Name, float Value)
{
	FBuffableValue* Temp = Values.Find(Name);
	if (Temp != nullptr)
	{
		Temp->Value = Value;
	}
	
}

float UBuffManagerComponent::GetValue(FName Name)
{
	FBuffableValue* Temp = Values.Find(Name);
	if (Temp != nullptr)
	{
		float Value = Temp->Value;
		EBuffAppliesTo Flags = Temp->AppliesTo_Flags;
	
		for (UBuff* Buff : Buffs)
		{
			if (HasFlag(Buff, Flags)) {
				Value = Buff->ApplyTo(Value);
			}
		}
		return Value;
	}
	return 0.f;
}

void UBuffManagerComponent::SetFlags(FName Name, const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags)
{
	FBuffableValue* Temp = Values.Find(Name);
	if (Temp != nullptr)
	{
		Temp->AppliesTo_Flags = ToSingleEnum(Flags);
	}
}

EBuffAppliesTo UBuffManagerComponent::ToSingleEnum(const TArray<TEnumAsByte<EBuffAppliesTo>>& Flags) const
{
	EBuffAppliesTo Temp = EBuffAppliesTo::NONE;
	for (EBuffAppliesTo Flag : Flags)
	{
		Temp = (EBuffAppliesTo)((uint8)Temp | (uint8)Flag);
	}
	return Temp;
}

bool UBuffManagerComponent::HasFlag(const UBuff* Buff, const EBuffAppliesTo& Flag) const
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("HATH FLAGGETH %i"), (uint8)Buff->AppliesTo[0]));
	return (Buff->AppliesTo_Flags & Flag) != EBuffAppliesTo::NONE;
}