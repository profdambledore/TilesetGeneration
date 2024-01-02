// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TreeSettings.generated.h"

USTRUCT(BlueprintType)
struct TILESETGENERATION_API FTreeSettings
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxBranchLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxNodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NodeRerolls;

	FTreeSettings();
	FTreeSettings(int NewBranchLength, int NewNodes, int NewNodeReroll);
	~FTreeSettings();
};
