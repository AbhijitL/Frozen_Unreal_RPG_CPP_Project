// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)){
        return;
    }

    FVector DesiredMovementThisFrame  = ConsumeInputVector().GetClampedToMaxSize(1.0f)*DeltaTime*150.0f;

    if(DesiredMovementThisFrame.IsNearlyZero()){
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame,UpdatedComponent->GetComponentRotation(),true,Hit);
        if(Hit.IsValidBlockingHit()){
            SlideAlongSurface(DesiredMovementThisFrame,1.0f-Hit.Time,Hit.Normal,Hit);
        }
    }

}