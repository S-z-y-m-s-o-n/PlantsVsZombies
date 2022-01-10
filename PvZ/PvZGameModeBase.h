// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PvZGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API APvZGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;
};
