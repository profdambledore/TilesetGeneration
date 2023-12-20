// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/RandomStream.h"

#include "Core/Data/TileData.h"
#include "Core/Data/TileNode.h"
#include "Core/Data/TileDoorType.h"

#include "TileManager.generated.h"

UCLASS()
class TILESETGENERATION_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	/// -- Defaults ---
	// Sets default values for this actor's properties
	ATileManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Generation ---
	// Called to generate a tile
	void GenerateNode(TEnumAsByte<ETileDoorType> DoorType, int ChildIndex);

	// Called to genearte a level with the current tile setting.  Will not work if a level is already generated
	void GenerateTileLevel(bool bGenerateNewSeed);

	// Called to clear the current generated level.  Will not work if no level is generated
	void ClearTileLevel();

	// Called to clear a generated level and generate a new one with the current tile setting.  Requires a level to be generated already. 
	void RegenerateTileLevel();

	// Called to generate a level via seed data.  Will update the tile and tree settings to match the seed
	void GenerateTileLevelFromSeed(int Seed);

	/// -- Tile Settings --
	// Called to return the current tile settings
	//void GetTileSettings();

	// Called to update the current tile settings.  Will not regenerate the level.
	//void SetTileSettings();

	// Called to find a tile from the data table that contain a tag
	TSubclassOf<ATile> GetTileMatchingTag(FName Tag);

	// Called to find a tile from the data table that contain a door type
	TSubclassOf<ATile> GetTileMatchingDoor(TEnumAsByte<ETileDoorType> DoorType);

	/// -- Tree Settings --
	// Called to return the current tree settings
	//void GetTreeSettings();

	// Called to update the current tree settings
	//void SetTreeSettings();

	/// -- Tree Query --
	// Called to add a new node to the level tree.  Returns true if a new node was created
	bool AddTreeNode(ATile* NewTile);

	// Called to remove a new node from the tree, as well as its children.  Returns true if the node was removed.
	//bool RemoveTreeNode()

	// Called to clear the tree.
	//void ClearTree();

	// Called to find a node in the tree via an index.  Returns the node pointer, or null if no tile is found.
	//NODEDATA* FindNodeFromIndex(int IndexToFind);

	// Called to get the last used node.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Tile Settings --
	// Data Table of all tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* TileDataTable = nullptr;

	/// -- Seed Settings --
	// Struct holding seed information
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Seed");
	FRandomStream SeedStream;

	// The current seed in use
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Seed");
	int CurrentSeed;

	/// -- Tree --
	// The level tree
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree");
	TArray<FTileNode> GeneratedTree;

	// Pointer to the current node in use
	int CurrentNode = -1;

	int CurrentBranchLength = 0;

	/// -- Tree Data --
	// The maximum branch length of the tree
	int MaxBranchLength = 3;
	// 
	// The maximum amount of nodes in the tree
	//int MaxNodes = 10; 
};
