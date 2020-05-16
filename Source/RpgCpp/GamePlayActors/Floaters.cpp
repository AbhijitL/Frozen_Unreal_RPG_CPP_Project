// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios


#include "Floaters.h"

// Sets default values
AFloaters::AFloaters()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

}

// Called when the game starts or when spawned
void AFloaters::BeginPlay()
{
	Super::BeginPlay();
	FVector initLoc = FVector(0.0f,0.0f,0.0f);
	SetActorLocation(initLoc);
}

// Called every frame
void AFloaters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

