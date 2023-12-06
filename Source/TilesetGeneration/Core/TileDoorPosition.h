// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Core/Data/TileDoorType.h"

#include "TileDoorPosition.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TILESETGENERATION_API UTileDoorPosition : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileDoorPosition();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// -- Door Position --
	// FName denoting the door positions name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// Enum denoting what type of connector should be used to connect this door
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETileDoorType> Type;



		
};
