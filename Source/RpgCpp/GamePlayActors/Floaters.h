// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floaters.generated.h"

UCLASS()
class RPGCPP_API AFloaters : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere,Category = "Static Mesh")
	UPrimitiveComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AFloaters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
