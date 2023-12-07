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
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::GenerateTileLevel()
{
	ATile* NewestTile = nullptr;
	if (TileDataTable) {
		// Start by finding a tile with the "Start" tag
		//NewestTile = UWorld::SpawnActor<ATile>(GetTileMatchingTag(FName("Spawn")), NAME_None, FVector(0.0f, 0.0f, 0.0f));
	}
}

//TSubclassOf<ATile> ATileManager::GetTileMatchingTag(FName Tag)
//{
	//TArray<TSubclassOf<ATile>> FoundTiles;

	//if (TileDataTable) {
		//TArray<FName> RowNames = TileDataTable->GetRowNames();
		//TArray<FName> CurrentTags;

		//for (FName i : RowNames) {
			//CurrentTags = TileDataTable->FindRow<FTileData>(i, "", false)->Tags;
			//if (Tags.Contains(Tag)) {
				//FoundTiles.Add(TileDataTable->FindRow<FTileData>(i, "", false)->Class);
			//}
		//}
	//}

	//if (FoundTiles.Num() != 0) {
		//return FoundTiles[FMath::RandRange(0, FoundTiles.Num() - 1)];
	//}
	//return NULL;
//}

bool ATileManager::AddTreeNode(ATile* NewTile)
{
	if (NewTile) {
		GeneratedTree.Add(FTileNode(NewTile, CurrentNode));
		return true;
	}
	return false;
}

