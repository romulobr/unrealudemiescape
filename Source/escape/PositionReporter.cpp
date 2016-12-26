// Fill out your copyright notice in the Description page of Project Settings.

#include "escape.h"
#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	
	auto location = GetOwner()->GetTransform().GetLocation();
	FString positionInformation = FString::Printf(TEXT("X=%f, Y=%f"), location.X, location.Y);

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objectName, *positionInformation);
	
}


// Called every frame
void UPositionReporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// ...
}

