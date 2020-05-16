// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UCLASS()
class RPGCPP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Item | collision")
	class USphereComponent* CollisionVolume;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Item | Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Item | Particle")
	class UParticleSystemComponent* IdleParticleComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | Particle")
	class UParticleSystem* OverlapParticles;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | itemProperties")
	bool bRotate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | itemProperties")
	float RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
