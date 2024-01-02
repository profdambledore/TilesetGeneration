// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/TreeSettings.h"

FTreeSettings::FTreeSettings()
{
}

FTreeSettings::FTreeSettings(int NewBranchLength, int NewNodes, int NewNodeReroll)
{
	MaxBranchLength = NewBranchLength;
	MaxNodes = NewNodes;
	NodeRerolls = NewNodeReroll;
}

FTreeSettings::~FTreeSettings()
{
}
