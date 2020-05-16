// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus : uint8 {
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_MoveToTarget UMETA(DisplayName = "MoveToTarget"),
	EMS_Attacking UMETA(DisplayName = "Attacking"),
	EMS_Death UMETA(DisplayName = "Death"),
	EMS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class RPGCPP_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	bool bHasValidTarget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	bool bShowDebugNavPath;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="AI")
	class USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "AI")
	class USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="AI")
	class AAIController* AIController;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Movement")
	EEnemyMovementStatus EnemyMovementStatus;

	FORCEINLINE void SetMovementEnemyStatus(EEnemyMovementStatus Status) { EnemyMovementStatus = Status; }

	FORCEINLINE EEnemyMovementStatus GetMovementEnemyStatus() { return EnemyMovementStatus; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	class USoundCue* HitSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	class USoundCue* SwingSound;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Combat")
	class UBoxComponent* CombatCollision;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat")
	float AttackMinTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat")
	float AttackMaxTime;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Combat")
	TSubclassOf<UDamageType> DamageTypeClass;

	FTimerHandle DeathTimer;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite, Category = "Combat")
	float DeathDelay;

	void Disappear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void MoveToTarget(class AMain* Target);

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category = "AI")
	bool bOverlappingCombatSphere;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="AI")
	AMain* CombatTarget;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="AI")
	float MaxHeath;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	float Health;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	float Damage;

	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void DeactivateCollision();

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Combat")
	class UAnimMontage* CombatMontage;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Combat")
	bool bAttacking;

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	void Attack();

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	bool Alive();
};
