// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Core/Data/TileDoorType.h"

#include "TileData.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTileData : public FTableRowBase
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATile> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<ETileDoorType>> Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Size;

	// Constructors / Destructors
	FTileData();
	~FTileData();
};

