// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Critter.generated.h"

UCLASS()
class RPGCPP_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACritter();

protected:
	// Called when the game starts or when spawned  
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnyWhere,BluePrintReadOnly,Category = "Mesh")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnyWhere,Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnyWhere)
	float MaxSpeed;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	FVector currentLocation;
};
