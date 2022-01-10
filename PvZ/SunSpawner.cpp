// Fill out your copyright notice in the Description page of Project Settings.


#include "SunSpawner.h"

#include "Kismet/GameplayStatics.h"

#include "PlayerPawn.h"

// Sets default values
ASunSpawner::ASunSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASunSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASunSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASunSpawner::Setup()
{
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ASunSpawner::SpawnSun, 5, true);
}

void ASunSpawner::SpawnSun()
{
	Cast<APlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass()))->SunCount += 50;
}

