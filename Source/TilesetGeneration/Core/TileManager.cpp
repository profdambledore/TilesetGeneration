// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TileManager.h"
#include "Core/Tile.h"
#include "Core/TileDoorPosition.h"
#include "Core/Data/TileChildren.h"

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

	GenerateTileLevel(true);
	//ClearTileLevel();
	//GenerateTileLevelFromSeed(21);
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::GenerateNode(TEnumAsByte<ETileDoorType> DoorType, int ChildIndex)
{
	if ((GeneratedTree[CurrentNode].Depth + 1) <= MaxBranchLength) {
		// Spawn a new child tile with a matching door, add it to the tree and update the parent
		ATile* ChildTile = GetWorld()->SpawnActor<ATile>(GetTileMatchingDoor(DoorType), FVector(0.0f, 0.0f, 0.0f), FRotator());
		AddTreeNode(ChildTile);
		GeneratedTree[CurrentNode].Children[ChildIndex].IndexToTile = GeneratedTree.Num() - 1;

		// Get a random doorway in that tile that matches the current door type and connect it to the parent
		int DoorIndex = ChildTile->GetMatchingDoorPosition(DoorType);
		GeneratedTree[GeneratedTree.Num() - 1].Children[DoorIndex].IndexToTile = CurrentNode;

		// Add the parent tile's offset to the new tile
		ChildTile->AddActorLocalRotation(GeneratedTree[CurrentNode].Tile->GetActorRotation()); //GeneratedTree[CurrentNode].Tile->Doors[ChildIndex].Object->GetRelativeRotation()
		ChildTile->AddActorLocalRotation(GeneratedTree[CurrentNode].Tile->Doors[ChildIndex].Object->GetRelativeRotation());

		// Find the dot product between the child tile doorway and the parent tile doorway
		FVector VecA = GeneratedTree[CurrentNode].Tile->Doors[ChildIndex].Object->GetForwardVector();
		VecA.Normalize();

		FVector VecB = ChildTile->Doors[DoorIndex].Object->GetForwardVector();
		VecB.Normalize();

		float OutAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(VecA, VecB)));

		//UE_LOG(LogTemp, Warning, TEXT("outangle = %f"), OutAngle);
		//UE_LOG(LogTemp, Warning, TEXT("corss z = %f"), FVector::CrossProduct(VecA, VecB).Z);

		// Calculate the cross product to determin what direction to rotate in
		// https://forums.unrealengine.com/t/how-to-get-an-angle-between-2-vectors/280850/39
		if (FVector::CrossProduct(VecA, VecB).Z > 0) 
		{
			OutAngle = -OutAngle;
		}

		//UE_LOG(LogTemp, Warning, TEXT("outangle after cross = %f"), OutAngle);

		// Rotate the tile so it is now facing the door
		ChildTile->AddActorLocalRotation(FRotator(0.0f, 180.0f, 0.0f));

		ChildTile->AddActorLocalRotation(FRotator(0.0f, OutAngle, 0.0f));

		// Finaly, move the new tile 
		ChildTile->AddActorWorldOffset(GeneratedTree[CurrentNode].Tile->Doors[ChildIndex].Object->GetComponentLocation() - ChildTile->Doors[DoorIndex].Object->GetComponentLocation());
	}
	
}

void ATileManager::GenerateTileLevel(bool bGenerateNewSeed)
{
	ATile* NewestTile = nullptr;
	//ATile* ParentTile = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("Generating"));

	if (bGenerateNewSeed) {
		// Make a new random seed
		CurrentSeed = FMath::RandRange(0, 2000);
		SeedStream = FRandomStream(CurrentSeed);
	}
	
	if (TileDataTable) {
		// First, create the starting tile
		// Start by finding a tile with the "Start" tag
		NewestTile = GetWorld()->SpawnActor<ATile>(GetTileMatchingTag(FName("Spawn")), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
		AddTreeNode(NewestTile);

		CurrentBranchLength++;

		// For each node in the tree
		for (int i = 0; i < GeneratedTree.Num(); i++) { //GeneratedTree.Num()
			CurrentNode = i;
			// For each child node of node i
			for (int j = 0; j < GeneratedTree[i].Children.Num(); j++) {
				// Generate a new tile
				if (GeneratedTree[i].Children[j].IndexToTile == -1) {
					GenerateNode(GeneratedTree[i].Children[j].Type, j);
				}
			}
		}
	}
}

void ATileManager::ClearTileLevel()
{
	if (GeneratedTree.Num() != 0) {
		// Iterate backwards through the tree from the final node, deleting every node and tile
		for (int i = GeneratedTree.Num() - 1; i > -1; i--) {
			GeneratedTree[i].Tile->Destroy();
		}

		// Garbage collect
		GEngine->ForceGarbageCollection();

		// Clear the tree
		GeneratedTree.Empty();
	}
}

void ATileManager::RegenerateTileLevel()
{
	ClearTileLevel();
	GenerateTileLevel(false);
}

void ATileManager::GenerateTileLevelFromSeed(int Seed)
{
	SeedStream = FRandomStream(Seed);
	GenerateTileLevel(false);
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

	//UE_LOG(LogTemp, Warning, TEXT("Amount Found: %i"), FoundTiles.Num());

	// If at least one tag was found, get a random tile found
	if (FoundTiles.Num() != 0) {
		return FoundTiles[SeedStream.RandRange(0, FoundTiles.Num() - 1)];
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

	//UE_LOG(LogTemp, Warning, TEXT("Amount Found: %i"), FoundTiles.Num());

	// If at least one tag was found, get a random tile found
	if (FoundTiles.Num() != 0) {
		return FoundTiles[SeedStream.RandRange(0, FoundTiles.Num() - 1)];
	}

	// Else, return null
	return NULL;
}

bool ATileManager::AddTreeNode(ATile* NewTile)
{
	if (NewTile) {
		FTileNode NewNode;
		if (GeneratedTree.Num() != 0) {
			NewNode = FTileNode(NewTile, CurrentNode, GeneratedTree[CurrentNode].Depth + 1);
		}
		else {
			NewNode = FTileNode(NewTile, CurrentNode, 1);
		}

		for (int i = 0; i < NewTile->Doors.Num(); i++) {
			NewNode.Children.Add(FTileChildren(NewTile->Doors[i].Name, NewTile->Doors[i].Type, -1));
		}

		GeneratedTree.Add(NewNode);
		return true;
	}
	return false;
}

