// Copyright Brad Lasecke 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
    
    self = GetOwner();
//    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(PressurePlate == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("%s does not have a connected PressurePlate, cannot open door"), *(GetOwner()->GetName()));
    }
}

//void UOpenDoor::OpenDoor() {
//    AActor* actor = GetOwner();
//    FRotator rot = FRotator(0.0f, openPos, 0.0f);
//    actor->SetActorRotation(rot);
//}
//
//void UOpenDoor::CloseDoor() {
//    AActor* actor = GetOwner();
//    FRotator rot = FRotator(0.0f, closedPos, 0.0f);
//    actor->SetActorRotation(rot);
//}

//void UOpenDoor::SetDoorRotation(float degrees) {
//    if(degrees >= float(openPos)) {
//        degrees = float(openPos);
//    }
//    else if(degrees <= float(closedPos)) {
//        degrees = float(closedPos);
//    }
//
//    FRotator rot = FRotator(0.0f, degrees, 0.0f);
//    self->SetActorRotation(rot);
//    currentPos = degrees;
//}
//
//bool UOpenDoor::isOpen() {
//    return currentPos >= float(openPos);
//}
//
//bool UOpenDoor::isClosed() {
//    return currentPos <= float(closedPos);
//}

float UOpenDoor::GetMassOfActorsOnPlate() {
    float m = 0.f;

    if(PressurePlate == nullptr) {
        return m;
    }
    
    //find all actors overlapping with this and add up their masses
    TArray<AActor*> actors;
    PressurePlate->GetOverlappingActors(actors);
    
    for(const auto* item : actors) {
        m += item->FindComponentByClass<UPrimitiveComponent>()->GetMass();
//        UE_LOG(LogTemp, Warning, TEXT("%s kgs on trigger plate"), *(item->GetName()));
    }
    
//    UE_LOG(LogTemp, Warning, TEXT("Checking mass"));
    return m;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    
//    bool shouldOpen = GetMassOfActorsOnPlate() > triggerMass;
//    if(!(isOpen() && shouldOpen) || !(isClosed() && !shouldOpen)) {
//        float rotDiff = abs(openRate*DeltaTime);
//        if(!shouldOpen) { rotDiff = -rotDiff; }
//
//        SetDoorRotation(currentPos+rotDiff);
//    }
    
    if(GetMassOfActorsOnPlate() > triggerMass) {
        onOpen.Broadcast();
    }
    else {
        onClose.Broadcast();
    }
}

