// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class RPGCPP_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category=FloorSwitch)
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category=FloorSwitch)
	class UStaticMeshComponent* FloorSwitch;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category=FloorSwitch)
	class UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadWrite,Category=FloorSwitch)
	FVector InitialDoorLocation;

	UPROPERTY(BlueprintReadWrite,Category=FloorSwitch)
	FVector InitialSwitchLocation;

	FTimerHandle SwitchHandle;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category=FloorSwitch)
	float SwitchTime;

	bool bCharacterOnSwitch;

	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent ,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor switch")
	void RaiseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor switch")
	void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor switch")
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor switch")
	void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable,Category = "Floor switch")
	void UpdateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable,Category = "Floor switch")
	void UpdateFloorSwitchLocation(float Z);
};
