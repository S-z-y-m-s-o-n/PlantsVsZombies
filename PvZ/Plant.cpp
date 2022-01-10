
#include "Plant.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "GridCell.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SetRootComponent(SkeletalMesh);
}

void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlant::Plant(AGridCell* GridCell)
{
	isPlanted = true;

	SkeletalMesh->SetMaterial(0, NormalMaterial);

	SetActorLocation(GridCell->GetActorLocation());
	SetActorRotation(FRotator(0, -90, 0));
	GridCell->IsOccupied = true;
}

void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

