
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PlayerPawn.generated.h"

UCLASS()
class PVZ_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SunCount = 50;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<class UUserWidget> SunCounterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plants")
		TSubclassOf<class APlant> WalnutClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plants")
		TSubclassOf<class APlant> SunflowerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plants")
		TSubclassOf<class APlant> PeaShooterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterialInterface* GridMaterial1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterialInterface* GridMaterial2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGridCell* GCL;

	TSubclassOf<class APlant> ChoosenPlantClass;

	class APlant* ChoosenPlant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AActor*> Grid;

	uint8 SelectedColumn = 0;
	uint8 SelectedRow = 0;

	class AGridCell* SelectedGridCell;
	
	FORCEINLINE void slot1() { ChoosePlant(SunflowerClass); }
	FORCEINLINE void slot2() { ChoosePlant(PeaShooterClass); }
	FORCEINLINE void slot3() { ChoosePlant(WalnutClass); }

	void SelectGridPosition(int i);
	void n1();
	void n2();
	void n3();
	void n4();
	void n5();
	void n6();
	void n7();
	void n8();
	void n9();
	void n10();

	void ClearGridChoice();

	void UnchoosePlant();

	void ChoosePlant(TSubclassOf<class APlant> PlantClass);

	void Confirm();

	void HighlightGrid();

	void Load();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
