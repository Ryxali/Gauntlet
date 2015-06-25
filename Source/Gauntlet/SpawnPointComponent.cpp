// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "SpawnPointComponent.h"
#include "ParticleDefinitions.h"
#include "Engine.h"
#include "math.h"
#include "GauntletCharacter.h"

// Sets default values for this component's properties
USpawnPointComponent::USpawnPointComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	struct FConstructorStatics
	{
		// A helper class object we use to find target UTexture2D object in resource package
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> MarkerTextureObject;
		// Icon sprite category name
		FName ID_CatagoryName;
			// Icon sprite display name
		FText NAME_DisplayName;
		FConstructorStatics()
			// Use helper class object to find the texture
			// "/Engine/EditorResources/S_Note" is resource path
			: MarkerTextureObject(TEXT("/Engine/EditorResources/S_Actor"))
			, ID_CatagoryName(TEXT("Marker"))
			, NAME_DisplayName(NSLOCTEXT("SpriteCategory", "AmmoMarker", "AmmoMarker"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	BillboardComponent = ObjectInitializer.CreateEditorOnlyDefaultSubobject<UBillboardComponent>(this, TEXT("Billboard"), true);
	SpriteTexture = ConstructorStatics.MarkerTextureObject.Get();
	
	
	BillboardComponent->Sprite = SpriteTexture;

	BillboardComponent->AttachTo(this);
}


// Called when the game starts
void USpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnPointComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USpawnPointComponent::OnRegister()
{
	// If we need to perform a call to AttachTo, do that now
	// At this point scene component still has no any state (rendering, physics),
	// so this call will just add this component to an AttachChildren array of a the Parent component
	AttachTo(AttachParent, AttachSocketName);
	Super::OnRegister();
}

void USpawnPointComponent::Spawn()
{
	//FMath::RandRange(0, Types.Num()-1);
	//UWorld::SpawnActor<Types[0]>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
	GetWorld()->SpawnActor(Types[0]->StaticClass());

	//UWorld::SpawnActor<AActor>();
	//UWorld::SpawnActor < Types[0]->StaticClass()>();
}