// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Main.h"

void UMainAnimInstance::NativeInitializeAnimation(){

    if(Pawn == nullptr){
        Pawn = TryGetPawnOwner();
		if (Pawn) {
			Main = Cast<AMain>(Pawn);
		}
    }

}

void UMainAnimInstance::UpdateAnimationProperties(){

    if(Pawn == nullptr){
        Pawn = TryGetPawnOwner();
    }

    if(Pawn){
        FVector Speed = Pawn->GetVelocity();
        FVector LateralSpeed = FVector(Speed.X,Speed.Y,0.0f);
        MovementSpeed = LateralSpeed.Size();

        bIsinAir = Pawn->GetMovementComponent()->IsFalling(); 

		if (Main == nullptr) {
			Main = Cast<AMain>(Pawn);
		}
    }

}