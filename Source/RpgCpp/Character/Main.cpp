// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios


#include "Main.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Combat/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/Enemy.h"
#include "GameplayMechanics/MainPlayerController.h"


// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom follow through the player if there a collision
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f; //Camera follow at this distance
	CameraBoom->bUsePawnControlRotation = true;//Rotates are based on controller

	//Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);//Make it attach to springarm CameraBoom
	FollowCamera->bUsePawnControlRotation = false;//Dont want the camera to move 

	//Values for Base turnUp and lookUp
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	//Dont rotate when the controller rotate just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Cofig charac movement 
	GetCharacterMovement()->bOrientRotationToMovement = true; // charac move in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);//at the rotation at yaw
	GetCharacterMovement()->JumpZVelocity = 650.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	/**Player Stats*/
	MaxHealth = 100.f;
	Health = 65.f;
	MaxStamina = 150.f;
	Stamina = 120.f;
	Coin = 0;
	StamindDrainRate = 25.f;
	MinSprintStamina = 50.0f;
	RunningSpeed = 650.f;
	SprintingSpeed = 950.f;

	InterpSpeed = 15.f;
	bInterpToEnemy = false;

	bShiftKeyDown = false;
	bLMBDown = false;

	bHasCombatTarget = false;

	//Initialize enums
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(GetController());
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementStatus == EMovementStatus::EMS_Death) return;

	float DeltaStamina = StamindDrainRate * DeltaTime;
	FVector Speed = GetVelocity();
	FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
	float MovementSpeed = LateralSpeed.Size();
	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal :
		if (bShiftKeyDown) {
			if (Stamina - DeltaStamina <= MinSprintStamina) {
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if(Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
			}
			else {
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if (Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
			}
			if (MovementSpeed == 0.0f) {
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else {
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
		}
		else {//if shifkey is up
			if(Stamina + DeltaStamina  >= MaxStamina){
				Stamina = MaxStamina;
			}
			else {
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if (bShiftKeyDown) {
			if (Stamina - DeltaStamina <= 0) {
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else {
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if (Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
				if (MovementSpeed == 0.0f) {
					SetMovementStatus(EMovementStatus::EMS_Normal);
				}
				else {
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
				}
			}
		}
		else {//if shift key is up
			if (Stamina + DeltaStamina >= MinSprintStamina) {
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaStamina;
			}
			else {
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bShiftKeyDown) {
			Stamina = 0.f;
		}
		else {// is shift key is up
			SetStaminaStatus(EStaminaStatus::ESS_ExhautedRecovering);
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	case EStaminaStatus::ESS_ExhautedRecovering:
		if (Stamina + DeltaStamina >= MinSprintStamina) {
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaStamina;
		}
		else {
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	default:
		;
	}

	if (bInterpToEnemy && CombatTarget) {
		FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
		FRotator InterRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw,DeltaTime,InterpSpeed);
		SetActorRotation(InterRotation);
	}
	if (CombatTarget) {
		CombatTargetLocation = CombatTarget->GetActorLocation();
		if (MainPlayerController) {
			MainPlayerController->EnemyLocation = CombatTargetLocation;
		}
	}
}

FRotator AMain::GetLookAtRotationYaw(FVector Target) {
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);
	return LookAtRotationYaw;
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMain::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this,&AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMain::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate",this,&AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate",this,&AMain::LookUpAtRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMain::ShiftKeyUp);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMain::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMain::LMBUp);

}
void AMain::MoveForward(float Value){
	if((Controller != nullptr) && (Value != 0.0) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Death)){
		//find out which way is Forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Value);
	}
}

void AMain::MoveRight(float Value){
	if((Controller != nullptr) && (Value != 0.0) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Death)){
		//find out which way is Forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction,Value);
	}
}



void AMain::TurnAtRate(float Rate){
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpAtRate(float Rate){
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::DecrementHealth(float Amount) {
	if (Health - Amount == 0.f) {
		Health -= Amount;
		Die();
	}
	else {
		Health -= Amount;
	}
}

void AMain::IncrementCoin(int32 Amount) {
	Coin += Amount;
}

void AMain::IncrementHealth(float Amount) {
	if (Health + Amount >= MaxHealth) {

		Health = MaxHealth;
	}
	else {
		Health += Amount;
	}
}

void AMain::Die() {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage) {
		AnimInstance->Montage_Play(CombatMontage, 1.0f);
		AnimInstance->Montage_JumpToSection(FName("Death"));
	}
	SetMovementStatus(EMovementStatus::EMS_Death);
}

void AMain::DeathEnd() {
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
}

void AMain::SetMovementStatus(EMovementStatus Status) {
	MovementStatus = Status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting) {
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMain::ShiftKeyDown() {
	bShiftKeyDown = true;
}

void AMain::ShiftKeyUp() {
	bShiftKeyDown = false;
}


void AMain::ShowPickupLocation() {
	for (int32 i = 0; i < PickUpLocation.Num(); i++) {

		UKismetSystemLibrary::DrawDebugSphere(this, PickUpLocation[i], 25.f, 8, FLinearColor::Green, 10.f, 0.5f);
	}

}


void AMain::LMBDown() {
	bLMBDown = true;
	if (MovementStatus == EMovementStatus::EMS_Death) return; 
	if (ActiveOverlappingItem) {
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);
		if (Weapon) {
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr);
		}
	}
	else if (EquippedWeapon) {
		Attack();
	}
}

void AMain::LMBUp() {
	bLMBDown = false;
}

void AMain::SetEquippedWeapon(AWeapon* WeaponToSet) {
	if (EquippedWeapon) {
		EquippedWeapon->Destroy();
	}
	EquippedWeapon = WeaponToSet;

}

void AMain::Jump(){
	if (MovementStatus != EMovementStatus::EMS_Death) {
		Super::Jump();
	}
}

void AMain::Attack() {
	if (!bAttacking && MovementStatus != EMovementStatus::EMS_Death) {
		bAttacking = true;
		SetInterpToEnemy(true);
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage) {
			int32 Section = FMath::RandRange(0, 1);
			switch (Section)
			{
			case 0:
				AnimInstance->Montage_Play(CombatMontage, 2.2f);
				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
				break;
			case 1:
				AnimInstance->Montage_Play(CombatMontage, 1.8f);
				AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
				break;
			default:
				break;
			}
		}
		
	}
}

void AMain::AttackEnd() {
	bAttacking = false;
	SetInterpToEnemy(false);
	if (bLMBDown) {
		Attack();
	}
}

void AMain::PlaySwingSound() {
	if (EquippedWeapon->SwingSound) {
		UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSound);
	}
}


void AMain::SetInterpToEnemy(bool Interp) {
	bInterpToEnemy = Interp;
}


float AMain::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	if (Health - DamageAmount == 0.f) {
		Health -= DamageAmount;
		Die();
		if (DamageCauser) {
			AEnemy* Enemy = Cast<AEnemy>(DamageCauser);
			if (Enemy) {
				Enemy->bHasValidTarget = false;
			}
		}
	}
	else {
		Health -= DamageAmount;
	}
	return DamageAmount;
}