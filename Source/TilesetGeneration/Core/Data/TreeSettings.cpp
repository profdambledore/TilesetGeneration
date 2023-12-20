// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/TreeSettings.h"

FTreeSettings::FTreeSettings()
{
}

FTreeSettings::FTreeSettings(int NewBranchLength, int NewNodes)
{
	MaxBranchLength = NewBranchLength;
	MaxNodes = NewNodes;
}

FTreeSettings::~FTreeSettings()
{
}
