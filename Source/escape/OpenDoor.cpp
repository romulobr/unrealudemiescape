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
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (TotalMassOfActorsOnPressurePlate() > 13.0f) {
		OpenDoor();
	}		
	else if (lastTimeOpen != 0.0f && world->GetTimeSeconds() - lastTimeOpen > secondsToClose) {
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	door->SetActorRotation(FRotator(0, openAngle, 0));
	lastTimeOpen = world->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	door->SetActorRotation(FRotator(0, closedAngle, 0));
	lastTimeOpen = 0.0f;
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