// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SpawnPointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), abstract, Blueprintable )
class GAUNTLET_API USpawnPointComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	virtual void OnRegister() override;
	// Sets default values for this component's properties
	USpawnPointComponent(const FObjectInitializer &ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	//UPROPERTY(EditDefaultsOnly, Category = Sprite)
	//class UTexture2D* Sprite;
	/** The different types to choose from when spawning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Types")
	TArray<TSubclassOf<class AActor>> Types;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spawn")
	void Spawn();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Types")
	
protected:
	//A UBillboardComponent to hold Icon sprite
	class UBillboardComponent* BillboardComponent;
	//Sprite for the Billboard Component
	class UTexture2D* SpriteTexture;
private:
		
	
};
