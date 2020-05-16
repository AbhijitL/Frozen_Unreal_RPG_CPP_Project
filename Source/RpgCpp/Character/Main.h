// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8 {
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Spirinting"),
	EMS_Death UMETA(DisplayName = "Death"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX"),
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8 {
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhautedRecovering UMETA(DisplayName = "ExhautedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax"),
};

UCLASS()
class RPGCPP_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Controller")
	class AMainPlayerController* MainPlayerController;

	bool bLMBDown;

	void LMBDown();

	void LMBUp();


	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	FRotator GetLookAtRotationYaw(FVector Target);

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Combat")
	class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	TArray<FVector> PickUpLocation;

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocation();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement")
	float StamindDrainRate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	/**Set movement status and running status */
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Running")
	float RunningSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	void ShiftKeyDown();

	void ShiftKeyUp();

	/** Camera boom  */
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category=Camera,meta= (AllowPrivateAccess = true))
	class USpringArmComponent* CameraBoom;
	
	/** Camera for the character*/
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category=Camera,meta= (AllowPrivateAccess = true))
	class UCameraComponent* FollowCamera;

	/**Base turn rate and base look up to control for camera*/
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category=Camera)
	float BaseLookUpRate;

	/**Health Stats*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Player Stats")
	float MaxHealth;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Stats")
	int32 Coin;

	UFUNCTION(BlueprintCallable)
	void IncrementCoin(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Amount);
	
	void DecrementHealth(float Amount);

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**function to handle movement input*/
	void MoveForward(float Value);
	void MoveRight(float Value);

	/**Calied via input to turn at rate : THis is a normalise rate , i.e,1.0 means 100% of desire turned rate*/
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {return CameraBoom;}
	FORCEINLINE class UCameraComponent* GetFollowCamera() const {return FollowCamera;}

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly, Category = "Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Anims")
	bool bAttacking;

	void Attack();



	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();
};
