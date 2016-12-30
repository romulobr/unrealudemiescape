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
	FVector playerLocation;
	FRotator playerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotator);

	FVector lineTraceEnd = (playerLocation + playerRotator.Vector() * reach);
	DrawDebugLine(
		GetWorld(), 
		playerLocation,
		lineTraceEnd, 
		FColor(255, 0, 0), 
		false, 
		0.0f, 
		0.0f, 
		2.0f);
	
	FHitResult hit;
	//FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	FCollisionQueryParams colisionQueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);


	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerLocation,
		lineTraceEnd,
		objectQueryParams,
		colisionQueryParams
	);
	auto actor = hit.GetActor();
	if(actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber in ta house!, loooking at %s , %s"), *(actor->GetName()));
	}		
}
