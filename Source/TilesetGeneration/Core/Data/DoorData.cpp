// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/DoorData.h"
#include "Core/TileDoorPosition.h"

FDoorData::FDoorData()
{
}

FDoorData::FDoorData(FName InName, TEnumAsByte<ETileDoorType> InType, UTileDoorPosition* InObject)
{
	Name = InName;
	Type = InType;
	Object = InObject;
}

FDoorData::~FDoorData()
{
}
