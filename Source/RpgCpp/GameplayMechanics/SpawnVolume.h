// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class RPGCPP_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnyWhere,BluePrintReadOnly,Category = "Spawning")
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Spawning")
	TSubclassOf<class AActor> Actor_1;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Spawning")
	TSubclassOf<class AActor> Actor_2;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Spawning")
	TSubclassOf<class AActor> Actor_3;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Spawning")
	TSubclassOf<class AActor> Actor_4;

	TArray<TSubclassOf<class AActor>> SpawnArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure,Category="Spawning")
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintPure, Category = "Spawning")
	TSubclassOf<class AActor> GetSpawnActor();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Spawning")
	void SpawnOurActor(UClass* ToSpawn, const FVector& Location);
};
