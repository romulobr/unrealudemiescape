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

void UGrabber::Grab() {
	auto component = lookingAt.GetComponent();
	auto actor = lookingAt.GetActor();

	if (lookingAt.GetComponent()) {
		physicsHandle->GrabComponentAtLocationWithRotation(component, NAME_None, holdingAt, actor->GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("grabbing"));
	}	
}

void UGrabber::Release() {
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("releasing"));
	}	
}

void UGrabber::findDependencies() {
	auto actor = GetOwner();
	physicsHandle = actor->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = actor->FindComponentByClass<UInputComponent>();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("physics handle not found on %s"), *(actor->GetName()));
	}
	if (!inputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("input not found on %s"), *(actor->GetName()));
	}
}

void UGrabber::bindInput() {
	inputComponent->BindAction("grab", IE_Pressed, this, &UGrabber::Grab);
	inputComponent->BindAction("grab", IE_Released, this, &UGrabber::Release);
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber in ta house!"));
	world = GetWorld();
	findDependencies();	
	bindInput();
}

void UGrabber::updateLookingAt() {
	FVector playerLocation;
	FRotator playerRotator;
	
	world->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotator);

	FVector lineTraceEnd = (playerLocation + playerRotator.Vector() * reach);
	holdingAt = lineTraceEnd;
	DrawDebugLine(
		world,
		playerLocation,
		lineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		2.0f);
	
	world->LineTraceSingleByObjectType(
		lookingAt,
		playerLocation,
		lineTraceEnd,
		objectQueryParams,
		colisionQueryParams
	);
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	updateLookingAt();
	physicsHandle->SetTargetLocation(holdingAt);
}
