// Copyright Brad Lasecke 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
    void SetDoorRotation(float degrees);
    bool isOpen();
    bool isClosed();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(VisibleAnywhere)
    float openAngle = 90.f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
	
//    UPROPERTY(EditAnywhere)
//    AActor* ActorThatOpens;
    AActor* self; //the door
    
    UPROPERTY(EditAnywhere)
    float triggerMass = 75.f;
    
    UPROPERTY(EditAnywhere)
    int openRate = 30; //degrees per second
    
    static const int openPos = 270;
    static const int closedPos = 180;
    float currentPos = 180.f;
    
    float GetMassOfActorsOnPlate();
};
