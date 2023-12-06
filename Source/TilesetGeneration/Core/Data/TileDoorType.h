// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Category = "Tile")
enum ETileDoorType
{
	Small UMETA(DisplayName = "Small Door"),
	Medium UMETA(DisplayName = "Medium Door"),
	Large UMETA(DisplayName = "Large Door"),
};