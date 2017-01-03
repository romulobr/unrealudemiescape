// Gordim @2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent onClose;

private:
	UPROPERTY(EditAnywhere)
	float triggerMass = 11.0f;

	UPROPERTY(EditAnywhere)
	float secondsToClose = 1.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* actorThatOpens;
	
	AActor* door;
	UWorld* world;

	float TotalMassOfActorsOnPressurePlate();
};
