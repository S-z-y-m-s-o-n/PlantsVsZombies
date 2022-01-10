

#include "PlayerPawn.h"

#include "Kismet/GameplayStatics.h"

#include "Plant.h"
#include "GridCell.h"
#include "SunSpawner.h"

#include "Blueprint/UserWidget.h"

#include "Camera/CameraComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridCell::StaticClass(), Grid);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

void APlayerPawn::Load()
{
	CreateWidget<UUserWidget>(GetGameInstance(), SunCounterClass)->AddToViewport();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridCell::StaticClass(), Grid);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	Cast<ASunSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ASunSpawner::StaticClass()))->Setup();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawn::ChoosePlant(TSubclassOf<APlant> PlantClass)
{
	ChoosenPlantClass = PlantClass;
	//FVector SpawnLocation;
	//FRotator SpawnRotation;

	//ChoosenPlant = GetWorld()->SpawnActor<APlant>(PlantClass.Get(), SpawnLocation, SpawnRotation);
}

void APlayerPawn::UnchoosePlant()
{
	if (ChoosenPlant != nullptr)
	{
		ChoosenPlant->Destroy();
	}
}

void APlayerPawn::ClearGridChoice()
{
	SelectedColumn = 0;
	SelectedRow = 0;
	SelectedGridCell = nullptr;
	HighlightGrid();
}

void APlayerPawn::Confirm()
{
	if (SelectedColumn != 0 && SelectedRow != 0 && ChoosenPlantClass != nullptr && !SelectedGridCell->IsOccupied) // && SunCount > ChoosenPlantClass.Get
	{
		APlant* SpawnedPlant = Cast<APlant>(GetWorld()->SpawnActor<APlant>(ChoosenPlantClass.Get()));
		SpawnedPlant->Plant(SelectedGridCell);
		SelectedColumn = 0;
		SelectedRow = 0;
		SelectedGridCell = nullptr;
		HighlightGrid();
		//SelectedGridCell->StaticMesh->SetVisibility(false);
	}
	else
	{
		ClearGridChoice();
	}
}

void APlayerPawn::HighlightGrid()
{
	if (SelectedColumn != 0)
	{
		for (uint8 i = 0; i < Grid.Num(); i++) // TArray<AGridCell*> GridCells;
		{
			AGridCell* GridCell = Cast<AGridCell>(Grid[i]);
			if (GridCell->GridPosition.Y == SelectedColumn)
			{
				GridCell->StaticMesh->SetMaterial(0, GridMaterial1);
				GridCell->StaticMesh->SetVisibility(true);
			}
		}
		if (SelectedRow != 0)
		{
			for (uint8 i = 0; i < Grid.Num(); i++) // TArray<AGridCell*> GridCells;
			{
				AGridCell* GridCell = Cast<AGridCell>(Grid[i]);
				if (GridCell->GridPosition.X == SelectedRow)
				{
					GridCell->StaticMesh->SetMaterial(0, GridMaterial1);
					GridCell->StaticMesh->SetVisibility(true);
				}
				if (GridCell->GridPosition.X == SelectedRow && GridCell->GridPosition.Y == SelectedColumn)
				{
					GridCell->StaticMesh->SetMaterial(0, GridMaterial2);
					GridCell->StaticMesh->SetVisibility(true);
					SelectedGridCell = GridCell;
				}
			}
		}
	}
	else
	{
		for (uint8 i = 0; i < Grid.Num(); i++)
		{
			AGridCell* GridCell = Cast<AGridCell>(Grid[i]);
			GridCell->StaticMesh->SetVisibility(false);
		}
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("UnchoosePlant", IE_Pressed, this, &APlayerPawn::UnchoosePlant);
	PlayerInputComponent->BindAction("Confirm", IE_Pressed, this, &APlayerPawn::Confirm);

	PlayerInputComponent->BindAction("ClearGridChoice", IE_Pressed, this, &APlayerPawn::ClearGridChoice);

	PlayerInputComponent->BindAction("Load", IE_Pressed, this, &APlayerPawn::Load);

	PlayerInputComponent->BindAction("s1", IE_Pressed, this, &APlayerPawn::slot1);
	PlayerInputComponent->BindAction("s2", IE_Pressed, this, &APlayerPawn::slot2);
	PlayerInputComponent->BindAction("s3", IE_Pressed, this, &APlayerPawn::slot3);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &APlayerPawn::n1);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &APlayerPawn::n2);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &APlayerPawn::n3);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &APlayerPawn::n4);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &APlayerPawn::n5);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &APlayerPawn::n6);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &APlayerPawn::n7);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &APlayerPawn::n8);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &APlayerPawn::n9);
	PlayerInputComponent->BindAction("10", IE_Pressed, this, &APlayerPawn::n10);
}

void APlayerPawn::SelectGridPosition(int num)
{
	if (SelectedColumn == 0)
	{
		SelectedColumn = num;
		HighlightGrid();
	}
	else if (SelectedRow == 0 && num < 6)
	{
		AGridCell* GridCell;
		for (uint8 i = 0; i < Grid.Num(); i++)
		{
			GridCell = Cast<AGridCell>(Grid[i]);
			if (GridCell->GridPosition == FVector2D(num, SelectedColumn) && !GridCell->IsOccupied)
			{
				SelectedRow = num;
				HighlightGrid();
				break;
			}
		}
	}
}

void APlayerPawn::n1()
{
	/*
	uint8 num = 1;
	if (SelectedColumn == 0)
	{
		SelectedColumn = num;
		HighlightGrid();
	}
	else if (SelectedRow == 0)
	{
		for (uint8 i = 0; i < Grid.Num(); i++)
		{
			AGridCell* GridCell = Cast<AGridCell>(Grid[i]);
			if (GridCell->GridPosition == FVector2D(SelectedColumn, num))
			{
				if (!GridCell->IsOccupied)
				{
					SelectedRow = num;
					HighlightGrid();
				}
				break;
			}
		}
	}
	*/
	SelectGridPosition(1);
}

void APlayerPawn::n2()
{
	SelectGridPosition(2);
}

void APlayerPawn::n3()
{
	SelectGridPosition(3);
}
void APlayerPawn::n4()
{
	SelectGridPosition(4);
}

void APlayerPawn::n5()
{
	SelectGridPosition(5);
}

void APlayerPawn::n6()
{
	SelectGridPosition(6);
}

void APlayerPawn::n7()
{
	SelectGridPosition(7);
}

void APlayerPawn::n8()
{
	SelectGridPosition(8);
}

void APlayerPawn::n9()
{
	SelectGridPosition(9);
}

void APlayerPawn::n10()
{
	SelectGridPosition(10);
}