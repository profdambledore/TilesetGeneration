// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/TileNode.h"

FTileNode::FTileNode()
{
}

FTileNode::FTileNode(ATile* NewTile, int NewParent, int NewDepth)
{
	Tile = NewTile;
	Parent = NewParent;
	Depth = NewDepth;
}

FTileNode::~FTileNode()
{
}
