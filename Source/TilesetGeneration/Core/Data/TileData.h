// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "TileData.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTileData : public FTableRowBase
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ATile> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Tags;

	// Constructors / Destructors
	FTileData();
	~FTileData();
};

