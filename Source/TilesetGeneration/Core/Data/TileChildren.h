// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Data/TileDoorType.h"

#include "TileChildren.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTileChildren
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DoorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETileDoorType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IndexToTile;


	// Constructors / Destructors
	FTileChildren();
	FTileChildren(FName InName, TEnumAsByte<ETileDoorType> InType, int InIndex);
	~FTileChildren();
};
