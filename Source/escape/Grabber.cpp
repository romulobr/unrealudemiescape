// Gordim @2016

#include "escape.h"
#include "Grabber.h"


void UGrabber::Grab() {
	auto component = lookingAt.GetComponent();
	auto actor = lookingAt.GetActor();

	if (component) {
		physicsHandle->GrabComponentAtLocationWithRotation(component, NAME_None, holdingAt, actor->GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("grabbing %s"), *(actor->GetName()));
	}	
}

void UGrabber::Release() {
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("releasing"));
	}
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	findDependencies();	
	bindInput();
}

void UGrabber::updateLookingAtAndHoldingAt() {
	OUT FVector playerLocation;
	OUT FRotator playerRotator;
	
	world->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotator);

	FVector lineTraceEnd = (playerLocation + playerRotator.Vector() * reach);	
	DrawDebugLine(world,playerLocation,lineTraceEnd,FColor(255, 100, 100),false,0.0f,0.0f,2.0f);	
	
	holdingAt = lineTraceEnd;
	world->LineTraceSingleByObjectType(lookingAt,playerLocation,lineTraceEnd,objectQueryParams,colisionQueryParams);
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	updateLookingAtAndHoldingAt();
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(holdingAt);
	}	
}

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::findDependencies() {
	world = GetWorld();
	auto actor = GetOwner();
	physicsHandle = actor->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = actor->FindComponentByClass<UInputComponent>();
}
void UGrabber::bindInput() {
	inputComponent->BindAction("grab", IE_Pressed, this, &UGrabber::Grab);
	inputComponent->BindAction("grab", IE_Released, this, &UGrabber::Release);
}
