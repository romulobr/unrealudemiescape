// Gordim @2016

#include "escape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
 {
	Super::BeginPlay();
	world = GetWorld();
	door = GetOwner();
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!pressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("No presure plate set for %s, door will never open"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );	
	if (pressurePlate && TotalMassOfActorsOnPressurePlate() > triggerMass) {
		onOpen.Broadcast();
	}		
	else {
		onClose.Broadcast();
	}
}

float UOpenDoor::TotalMassOfActorsOnPressurePlate() {
	OUT TArray<AActor*> actors;
	pressurePlate->GetOverlappingActors(actors);
	
	float sum = 0.0f;
	for (const auto& actor : actors) {
		auto primitive = actor->FindComponentByClass<UPrimitiveComponent>();
		sum += primitive->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("mass: %f, total: %f"), primitive->GetMass(), sum);
	}
	return sum;
}