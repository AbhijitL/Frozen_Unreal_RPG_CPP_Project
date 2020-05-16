// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class RPGCPP_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnyWhere,Category="MeshComponent")
	class UStaticMeshComponent* MeshComponent;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent(){return MeshComponent;}
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh){MeshComponent = Mesh;}

	UPROPERTY(VisibleAnyWhere,Category="SphereComponent")
	class USphereComponent* SphereComponent;

	FORCEINLINE USphereComponent* GetSphereComponent(){return SphereComponent;}
	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere){SphereComponent = Sphere;}

	UPROPERTY(VisibleAnyWhere,Category="CameraComponent")
	class UCameraComponent* Camera;

	FORCEINLINE UCameraComponent* GetCameraComponent(){return Camera;}
	FORCEINLINE void SetCameraComponent(UCameraComponent* InCamera){Camera = InCamera;}

	UPROPERTY(VisibleAnyWhere,Category="CameraComponet")
	class USpringArmComponent* SpringArm;

	FORCEINLINE USpringArmComponent* GetSpringComponent(){return SpringArm;}
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* InSpringArm){SpringArm = InSpringArm;}

	UPROPERTY(VisibleAnyWhere,Category = "MovementComponent")
	class UColliderMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
};
