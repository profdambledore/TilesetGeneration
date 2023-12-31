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
	if (Doors.Num() == 0) {
		// Get all TileDoorPositions attached to this Tile
		TArray<UTileDoorPosition*> TDP;
		GetComponents<UTileDoorPosition>(TDP);

		//UE_LOG(LogTemp, Warning, TEXT("TileDoorPositions found : %i"), TDP.Num());

		// Then sort them into the maps
		for (UTileDoorPosition* i : TDP) {
			Doors.Add(FDoorData(i->Name, i->Type, i));
		}
	}
}

int ATile::GetMatchingDoorPosition(TEnumAsByte<ETileDoorType> InType, FRandomStream SeedStream)
{
	int MatchingDoors = 0;
	TArray<int> indec;

	for (int i = 0; i < Doors.Num(); i++) {
		if (Doors[i].Type == InType) {
			indec.Add(i);
		}
	}

	if (indec.Num() > 0) {
		int ran = SeedStream.RandRange(0, indec.Num() - 1);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Doors[ran].Name.ToString());
		return indec[ran];
	}
	UE_LOG(LogTemp, Warning, TEXT("out of band"));
	return 0;
}

