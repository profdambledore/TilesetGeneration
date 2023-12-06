// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tile.h"
#include "Core/TileDoorPosition.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get all TileDoorPositions attached to this Tile
	TArray<UTileDoorPosition*> TDP;
	GetComponents<UTileDoorPosition>(TDP);

	// Then sort them into the maps
	for (UTileDoorPosition* i : TDP) {
		DoorPositions.Add(i->Name, i);
		Doors.Add(i->Name, i->Type);
	}

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

