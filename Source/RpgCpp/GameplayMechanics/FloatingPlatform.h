// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class RPGCPP_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Platform")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnyWhere)
	FVector StartPoint;

	UPROPERTY(EditAnyWhere,meta = (MakeEditWidget = "true"))
	FVector EndPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Platform")
	float InterpSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Platform")
	float InterpTime;

	FTimerHandle InterpTimer;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Platform")
	bool bInterping;

	float Distance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleInterping();

	void SwapVectors(FVector& VecOne, FVector& VecTwo);
};
