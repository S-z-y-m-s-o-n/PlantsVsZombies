
#include "GridCell.h"

#include "Components/StaticMeshComponent.h"

AGridCell::AGridCell()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AGridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

