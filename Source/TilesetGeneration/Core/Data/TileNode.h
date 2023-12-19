// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Tile.h"
#include "Core/Data/TileChildren.h"

#include "TileNode.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTileNode
{
public:
	GENERATED_BODY();

	// Pointer to the Tile object in the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATile* Tile;

	// Int of the index of this tiles parent node
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Parent;

	// Array of 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTileChildren> Children;


	// Constructors / Destructors
	FTileNode();
	FTileNode(ATile* NewTile, int NewParent);
	~FTileNode();
};
