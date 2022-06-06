#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "crafting_system_001/Scripts/Pawns/UpgradeManagerComponent.h"
#include "GarageWidget.generated.h"

class UUpgradeManagerComponent;

UCLASS()
class CRAFTING_SYSTEM_001_API UGarageWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	/*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TitleTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TestUpgradeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TestUpgradeButtonText;

	UFUNCTION()
		void TestButtonOnClicked();
	*/

	//Upgrade Buttons

	//Turret
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TurretButtonT1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TurretButtonT2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TurretButtonT3;

	//Chassis
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ChassisButtonT1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ChassisButtonT2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ChassisButtonT3;

	//Engine
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* EngineButtonT1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* EngineButtonT2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* EngineButtonT3;

	//Upgrade Button Functions

	//Turret
	UFUNCTION()
		void TurretButtonT1OnClicked();

	UFUNCTION()
		void TurretButtonT2OnClicked();

	UFUNCTION()
		void TurretButtonT3OnClicked();

	//Chassis
	UFUNCTION()
		void ChassisButtonT1OnClicked();

	UFUNCTION()
		void ChassisButtonT2OnClicked();

	UFUNCTION()
		void ChassisButtonT3OnClicked();

	//Engine
	UFUNCTION()
		void EngineButtonT1OnClicked();

	UFUNCTION()
		void EngineButtonT2OnClicked();

	UFUNCTION()
		void EngineButtonT3OnClicked();


	//Stats
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* HealthStatTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* DamageStatTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* SpeedStatTextBlock;


	//Resources/Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ArmourPlateText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CircuitBoardText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CogText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ScrapText;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XConfiguration")
		FString TestTextWidgetString;

	void InitUpgradeComponent(UUpgradeManagerComponent* upgradeComponent);

	//Stats Method - needs to be public to call from upgrade manager
	UFUNCTION()
		void UpdateStatsTextBlocks(float health, float damage, float speed);

	//cogs, circuit boards, scrap, armour plates.
	UFUNCTION()
		void UpdateComponentsTextBlocks(int cogs, int circuitBoards, int scrap, int armourPlates);

private:

	UUpgradeManagerComponent* mUpgradeComponent = nullptr;
};