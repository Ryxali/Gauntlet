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
	for (auto It(Buffs.CreateIterator()); It; It++) // Remove decayed buffs
	{
		if (!(*It)->IsValidLowLevel()) continue;
		float SecondsPassed = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		if ((*It)->EndTime < SecondsPassed)
		{
			//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Killed Buff!"));
			(*It)->ConditionalBeginDestroy();
			Buffs.RemoveAt(It.GetIndex());
			It--;
		}
	}
	// ...
}



void UBuffManagerComponent::AddBuff(TSubclassOf<UBuff> Buff)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Adding Buff"));
	if (Buff == NULL) return;
	for (UBuff* Tmp : Buffs)
	{
		if (Tmp->GetClass() == Buff)
		{
			if (Tmp->RefreshDuplicatesOnAdd && GetWorld()->IsValidLowLevel())
			{
				Tmp->StartDecay(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
			}
			if (Tmp->IsUnique)
			{
				return;
			}
		}
	}
	UBuff* p = NewObject<UBuff>((UObject*)GetTransientPackage(), Buff);
	if (GetWorld()->IsValidLowLevel())
	{ 
		p->SetWorld(GetWorld());
		p->StartDecay(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Cannot get world time for buff!"));
	}
	p->Host = GetOwner();
	Buffs.Add(p);
}

void UBuffManagerComponent::OnHit(AActor* HitActor)
{
	for (UBuff* Tmp : Buffs)
	{
		if (Tmp->IsValidLowLevel())
		{
			Tmp->OnHit(HitActor);
		}
	}
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

float UBuffManagerComponent::GetValue(FName Name) const
{
	const FBuffableValue* Temp = Values.Find(Name);
	if (Temp != nullptr)
	{
		float Value = Temp->Value;
		EBuffAppliesTo Flags = Temp->AppliesTo_Flags;
	
		for (UBuff* Buff : Buffs)
		{
			if (HasFlag(Buff, Flags)) {
				Value = Buff->ApplyTo(Temp->Value, Value);
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

void UBuffManagerComponent::CleanseBuffs()
{
	for (auto It(Buffs.CreateIterator()); It; It++)
	{
		if (!(*It)->IsValidLowLevel() && !(*It)->CanBeCleansed) continue;
		(*It)->ConditionalBeginDestroy();
		Buffs.RemoveAt(It.GetIndex());
		It--;
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
	return (Buff->AppliesTo_Flags & Flag) != EBuffAppliesTo::NONE;
}