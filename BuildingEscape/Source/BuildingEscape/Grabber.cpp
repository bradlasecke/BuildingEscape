// Copyright Brad Lasecke 2017

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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
	
    UE_LOG(LogTemp, Warning, TEXT("Grabber.cpp"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    
    /// Get player viewpoint and rotation
    AActor* actor = GetOwner();
    FVector viewpoint = actor->GetTransform().GetLocation();
    FRotator rot = actor->GetActorRotation();
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewpoint, rot);
    
//    UE_LOG(LogTemp, Warning, TEXT("Pos: %s, Rot: %s"), *(viewpoint.ToString()), *(rot.ToString()));
    
    FVector lineTraceEnd = viewpoint + rot.Vector()*Reach;
    
    /// Draw a red trace to see where the player is pointing
//    DrawDebugLine(GetWorld(), viewpoint, //start
//                  lineTraceEnd, //end
//                  FColor(245, 64, 50), //color
//                  false, //dont remember
//                  0.f, // ^^
//                  0.f, // ^^
//                  10.f); //thickness of line
    
    ///query params
    FCollisionQueryParams traceParams(FName(TEXT("")), //tag
                          false, //use complex body physics
                          GetOwner()); //actor to ignore
    
    FHitResult hit;
    GetWorld()->LineTraceSingleByObjectType(hit,
                                            viewpoint,
                                            lineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            traceParams);
    
    AActor* hitActor = hit.GetActor();
    if(hitActor) {
        UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *(hitActor->GetName()));
    }
}

