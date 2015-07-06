// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OptionsManager.generated.h"

USTRUCT()
struct FOptionsSettings {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int8 someval;

	FOptionsSettings() : someval(0)
	{

	}
};

/**
 * 
 */
UCLASS()
class GAUNTLET_API UOptionsManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	* Initialize the game with previously saved options
	*/
	UFUNCTION(BlueprintCallable, Category="Options")
	void LoadSavedOptions();
	
	/**
	* Apply current settings to game. 
	*/
	UFUNCTION(BlueprintCallable, Category = "Options")
	void ApplyCurrent();


};
