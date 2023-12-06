// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TileManager.h"
#include "Core/Tile.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get Data Table object and store it
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT(""));
	if (DTObject.Succeeded()) { TileDataTable = DTObject.Object; }

}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::GenerateTileLevel()
{
}

