// Copyright Brad Lasecke 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float Reach = 190.f; //distance grabber can "reach" in cm
	
    UPhysicsHandleComponent* physHandle = nullptr;
    UInputComponent* input = nullptr;
    
    void AssignComponents();
    FHitResult GetFirstPhysicsBodyInReach();
    FVector getLineTraceEnd();
    
    //ray cast and grab what is in reach
    void Grab();
    
    void Release();
};
