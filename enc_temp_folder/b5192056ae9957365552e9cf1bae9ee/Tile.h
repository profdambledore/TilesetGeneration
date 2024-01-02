// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Core/Data/TileDoorType.h"
#include "Core/Data/DoorData.h"

#include "Tile.generated.h"

UCLASS()
class TILESETGENERATION_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	/// -- Defaults ---
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Generation --
	// Called to get the positions of this tiles connectors

	// Called to get all the TileDoorPositions and push them into the array
	UFUNCTION(BlueprintCallable)
	void GetTileDoorPositions();

	// Called to return a random TileDoorPosition that matches an inputted door type
	int GetMatchingDoorPosition(TEnumAsByte<ETileDoorType> InType);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDoorData> Doors;
};
