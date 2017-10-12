// Copyright Brad Lasecke 2017

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"


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

	// ...
	
//    UE_LOG(LogTemp, Warning, TEXT("Grabber.cpp"));
    
    AssignComponents();
}

void UGrabber::AssignComponents() {
    /// Look for attached Physics handle - only appears at runtime
    physHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(physHandle) {
        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s does not have a UPhysicsHandleComponent, cannot grab objects"), *(GetOwner()->GetName()));
    }
    
    /// Look for attached Input handle - only appears at runtime
    input = GetOwner()->FindComponentByClass<UInputComponent>();
    if(input) {
        ///bind input action
        input->BindAction("Grab", //action name (Settings>Project Settings>Input>action_name)
                          IE_Pressed, //key event enum
                          this, //"this" is the Grabber object
                          &UGrabber::Grab); // ?????
        
        input->BindAction("Grab", //action name (Settings>Project Settings>Input>action_name)
                          IE_Released, //key event enum
                          this, //"this" is the Grabber object
                          &UGrabber::Release); // ?????
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s does not have a UInputComponent, cannot receive input"), *(GetOwner()->GetName()));
    }
}

void UGrabber::Grab() {
//    UE_LOG(LogTemp, Warning, TEXT("Grabbing!"));
    auto hit = GetFirstPhysicsBodyInReach();
    auto hitActor = hit.GetActor();
    auto compToGrab = hit.GetComponent();
    
    if(hitActor) {
        UE_LOG(LogTemp, Warning, TEXT("Grabbed %s"), *(hitActor->GetName()));
        physHandle->GrabComponentAtLocationWithRotation(compToGrab,
                                                        NAME_None,
                                                        hitActor->GetActorLocation(),
                                                        hitActor->GetActorRotation());
    }
}

void UGrabber::Release() {
//    UE_LOG(LogTemp, Warning, TEXT("Releasing!"));
    physHandle->ReleaseComponent();
}

FVector UGrabber::getLineTraceEnd() {
    AActor* actor = GetOwner();
    FVector viewpoint = actor->GetTransform().GetLocation();
    FRotator rot = actor->GetActorRotation();
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewpoint, rot);
    
    return (viewpoint + rot.Vector()*Reach);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    FVector viewpoint = GetOwner()->GetTransform().GetLocation();
    FVector lineTraceEnd = getLineTraceEnd();
    
    ///query params
    FCollisionQueryParams traceParams(FName(TEXT("")), //tag
                                      false, //use complex body physics
                                      GetOwner()); //actor to ignore
    
    FHitResult hit;
    GetWorld()->LineTraceSingleByObjectType(hit, //variable to store FHitResult in
                                            viewpoint, //start
                                            lineTraceEnd, //end
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //search only for physics body objects
                                            traceParams);
    return hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    
    
    /// Draw a red trace to see where the player is pointing
//    DrawDebugLine(GetWorld(), viewpoint, //start
//                  lineTraceEnd, //end
//                  FColor(245, 64, 50), //color
//                  false, //dont remember
//                  0.f, // ^^
//                  0.f, // ^^
//                  10.f); //thickness of line
    
    //if attached physics body, move physics body with user movement
    if(physHandle->GrabbedComponent) {
        physHandle->SetTargetLocation(getLineTraceEnd());
    }
}

