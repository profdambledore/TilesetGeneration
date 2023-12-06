// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Tile.h"

#include "TileNode.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTileNode
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATile* Tile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int> Children;


	// Constructors / Destructors
	FTileNode();
	FTileNode(ATile* NewTile, int NewParent);
	~FTileNode();
};
