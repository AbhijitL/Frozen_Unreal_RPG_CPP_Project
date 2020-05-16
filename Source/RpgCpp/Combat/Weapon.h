// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios
#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	EWS_PickUp UMETA(DisplayName = "Pickup"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_MAX UMETA(DisplaName="DefaultMax")
};

/**
 * 
 */
UCLASS()
class RPGCPP_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Item")
	EWeaponState WeaponState;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | Particles")
	bool bWeaponParticle;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Item | Sound")
	class USoundCue* OnEquipSound;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh; 

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Item | Combat")
	float Damage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item | Sound")
	USoundCue* SwingSound;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Combat")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(VisibleANyWhere,BlueprintReadOnly,Category="Combat")
	AController* WeaponInstigator;

	FORCEINLINE void SetInstigator(AController* Inst) { WeaponInstigator = Inst; }


protected:

	virtual void BeginPlay() override;

public:

	void Equip(class AMain* Char);

	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State;	 }
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Item | Combat")
	class UBoxComponent* CombatCollision;

	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void DeactivateCollision();
};
