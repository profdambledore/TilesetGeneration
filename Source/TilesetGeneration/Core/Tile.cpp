// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tile.h"
#include "Core/TileDoorPosition.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Testewr();

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

void ATile::GetTileDoorPositions()
{
	// Check if the maps are empty.  If they are, then...
	if (DoorPositions.Num() == 0) {
		// Get all TileDoorPositions attached to this Tile
		TArray<UTileDoorPosition*> TDP;
		GetComponents<UTileDoorPosition>(TDP);

		UE_LOG(LogTemp, Warning, TEXT("TileDoorPositions found : %i"), TDP.Num());

		// Then sort them into the maps
		for (UTileDoorPosition* i : TDP) {
			DoorPositions.Add(i->Name, i);
			Doors.Add(i->Name, i->Type);
		}
	}
}

