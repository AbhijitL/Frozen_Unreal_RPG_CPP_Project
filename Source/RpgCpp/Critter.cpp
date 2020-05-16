// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#include "Critter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACritter::ACritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent-> SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.0f,0.0f,300.0f));
	Camera->SetRelativeRotation(FRotator(-45.f,0.0f,0.0f));  

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	currentLocation = FVector(0.0f);
	MaxSpeed = 100;
}


// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = GetActorLocation() + (currentLocation * DeltaTime);
	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACritter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACritter::MoveRight);

}

void ACritter::MoveForward(float Value){
	currentLocation.X = FMath::Clamp(Value,-1.f,1.f) * MaxSpeed; 
}
void ACritter::MoveRight(float Value){
	currentLocation.Y = FMath::Clamp(Value,-1.f,1.f) * MaxSpeed;
}