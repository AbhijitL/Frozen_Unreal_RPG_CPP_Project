// CopyRight to Abhijit Leihaorambam abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPGCPP_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category= "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widgets")
	class UUserWidget* HUDOverlay;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Widgets")
	TSubclassOf<UUserWidget> WEnemyHealthBar;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Widgets")
	UUserWidget* EnemyHealthBar;

	bool bEnemyHealthBarVisible;

	void DisplayEnemyHealthBar();
	void RemoveEnemyHealthBar();

	FVector EnemyLocation;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
