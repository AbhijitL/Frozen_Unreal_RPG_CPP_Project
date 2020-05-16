// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Item.h"
#include "Explosive.generated.h"

/**
 * 
 */
UCLASS()
class RPGCPP_API AExplosive : public AItem
{
	GENERATED_BODY()
public:
	AExplosive();

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Damage")
	float Damage;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
