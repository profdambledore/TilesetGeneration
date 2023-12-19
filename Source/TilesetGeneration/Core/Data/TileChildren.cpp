// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/TileChildren.h"

FTileChildren::FTileChildren()
{
}

FTileChildren::FTileChildren(FName InName, TEnumAsByte<ETileDoorType> InType, int InIndex)
{
	DoorName = InName;
	Type = InType;
	IndexToTile = InIndex;
}

FTileChildren::~FTileChildren()
{
}
