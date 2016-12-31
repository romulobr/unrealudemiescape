// Gordim @2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	void updateLookingAt();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	
	const FCollisionQueryParams colisionQueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	const FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	const float reach = 100.0f;
	
	FVector holdingAt;
	UWorld* world = nullptr;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;
	FHitResult lookingAt;
	
	void Grab();
	void Release();
	void findDependencies();
	void bindInput();
};
