
#pragma once

#include "PlayerPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plant.generated.h"

UCLASS()
class PVZ_API APlant : public AActor
{
	GENERATED_BODY()

public:	
	APlant();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterial* NormalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterial* TranslucentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int MaxHealth;

	//static int SunCost;

	uint16 Health;

	void Plant(class AGridCell* GridCell);

protected:
	virtual void BeginPlay() override;

private:
	bool isPlanted = false;

public:	
	virtual void Tick(float DeltaTime) override;

};
