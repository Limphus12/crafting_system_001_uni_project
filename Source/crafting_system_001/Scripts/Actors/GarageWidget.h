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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TitleTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TestUpgradeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TestUpgradeButtonText;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
		void TestButtonOnClicked();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XConfiguration")
		FString TestTextWidgetString;

	void InitUpgradeComponent(UUpgradeManagerComponent* upgradeComponent);

private:

	UUpgradeManagerComponent* mUpgradeComponent = nullptr;
};