// Gordim @2016

#include "escape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber in ta house!"));
	
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector location;
	FRotator rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotator);
	FVector lineTrace = (location + rotator.Vector() * 10);
	DrawDebugLine(GetWorld(), lineTrace, lineTrace + FVector(100.0f, 100.0f, 100.0f) * reach, FColor(255, 0, 0), false, 0, 0, 2.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber in ta house!, loooking at %s , %s"), *location.ToString(), *rotator.ToString());
	
}

