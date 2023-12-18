// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TileManager.h"
#include "Core/Tile.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get Data Table object and store it
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Tileset/DT_TileData"));
	if (DTObject.Succeeded()) { TileDataTable = DTObject.Object; }

}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateTileLevel();
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::GenerateTileLevel()
{
	ATile* NewestTile = nullptr;
	ATile* ParentTile = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("Generating"));

	if (TileDataTable) {
		// First, create the starting tile
		// Start by finding a tile with the "Start" tag
		NewestTile = GetWorld()->SpawnActor<ATile>(GetTileMatchingTag(FName("Spawn")), FVector(0.0f, 0.0f, 0.0f), FRotator());
		AddTreeNode(NewestTile);

		ParentTile = NewestTile;
		CurrentNode = 0;

		// Then, for each doorway in the spawn tile, create a child tile and connect them together
		for (int i = 0; i < ParentTile->Doors.Num(); i++) {
			// Find a tile with a door and spawn it
			NewestTile = GetWorld()->SpawnActor<ATile>(GetTileMatchingDoor(ParentTile->Doors[i].Type), FVector(0.0f, 0.0f, 0.0f), FRotator());
			AddTreeNode(NewestTile);
			GeneratedTree[CurrentNode].Children.Add(ParentTile->Doors[0].Name, GeneratedTree.Num() - 1);

			// Get a random doorway in that tile that matches the current door type and connect it to the parent
			int DoorIndex = NewestTile->GetMatchingDoorPosition(ParentTile->Doors[i].Type);
			GeneratedTree[CurrentNode + i + 1].Children.Add(NewestTile->Doors[DoorIndex].Name, CurrentNode);
		}
	}
}

TSubclassOf<ATile> ATileManager::GetTileMatchingTag(FName Tag)
{
	// Initialize a storing array
	TArray<TSubclassOf<ATile>> FoundTiles;

	// Check if the data table is found
	if (TileDataTable) {
		// Store all of the row names in the data table, and initilize an array to store tags found
		TArray<FName> RowNames = TileDataTable->GetRowNames();
		TArray<FName> CurrentTags;

		// For each element in the data table, check that its tag array contains the tag wanted.  If it does, add it to the FoundTiles array
		for (FName i : RowNames) {
			CurrentTags = TileDataTable->FindRow<FTileData>(i, "", false)->Tags;
			if (CurrentTags.Contains(Tag)) {
				FoundTiles.Add(TileDataTable->FindRow<FTileData>(i, "", false)->Class);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Amount Found: %i"), FoundTiles.Num());

	// If at least one tag was found, get a random tile found
	if (FoundTiles.Num() != 0) {
		return FoundTiles[FMath::RandRange(0, FoundTiles.Num() - 1)];
	}

	// Else, return null
	return NULL;
}

TSubclassOf<ATile> ATileManager::GetTileMatchingDoor(TEnumAsByte<ETileDoorType> DoorType)
{
	// Initialize a storing array
	TArray<TSubclassOf<ATile>> FoundTiles;

	// Check if the data table is found
	if (TileDataTable) {
		// Store all of the row names in the data table, and initilize an array to store tags found
		TArray<FName> RowNames = TileDataTable->GetRowNames();
		TArray<TEnumAsByte<ETileDoorType>> CurrentDoorTypes;

		// For each element in the data table, check that its tag array contains the tag wanted.  If it does, add it to the FoundTiles array
		for (FName i : RowNames) {
			CurrentDoorTypes = TileDataTable->FindRow<FTileData>(i, "", false)->Doors;
			if (CurrentDoorTypes.Contains(DoorType)) {
				FoundTiles.Add(TileDataTable->FindRow<FTileData>(i, "", false)->Class);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Amount Found: %i"), FoundTiles.Num());

	// If at least one tag was found, get a random tile found
	if (FoundTiles.Num() != 0) {
		return FoundTiles[FMath::RandRange(0, FoundTiles.Num() - 1)];
	}

	// Else, return null
	return NULL;
}

bool ATileManager::AddTreeNode(ATile* NewTile)
{
	if (NewTile) {
		FTileNode NewNode = FTileNode(NewTile, CurrentNode);

		for (int i = 0; i < NewTile->Doors.Num(); i++) {
			NewNode.Children.Add(NewTile->Doors[i].Name, -1);
		}

		GeneratedTree.Add(NewNode);
		return true;
	}
	return false;
}

