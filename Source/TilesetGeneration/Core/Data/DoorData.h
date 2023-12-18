// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Data/TileDoorType.h"

#include "DoorData.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FDoorData
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETileDoorType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTileDoorPosition* Object;


	FDoorData();
	FDoorData(FName InName, TEnumAsByte<ETileDoorType> InType, UTileDoorPosition* InObject);
	~FDoorData();
};
