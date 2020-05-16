// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Item.h"
#include "PickUp.generated.h"

/**
 * 
 */
UCLASS()
class RPGCPP_API APickUp : public AItem
{
	GENERATED_BODY()
public:
	APickUp();

	UFUNCTION(BlueprintImplementableEvent,Category="Pickup")
	void OnPickUpBP(class AMain* Target);

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
