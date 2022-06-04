#include "GarageWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "crafting_system_001/Scripts/Pawns/UpgradeManagerComponent.h"

class UUpgradeManagerComponent;


void UGarageWidget::NativeConstruct()
{
	if (TestUpgradeButton && TestUpgradeButtonText)
	{
		//Binding the testbuttononclicked method to the button
		TestUpgradeButton->OnClicked.AddDynamic(this, &UGarageWidget::TestButtonOnClicked); 

		//InitUpgradeComponent();
	}
}

void UGarageWidget::InitUpgradeComponent(UUpgradeManagerComponent* upgradeComponent)
{
	check(mUpgradeComponent == nullptr);
	mUpgradeComponent = upgradeComponent;

	if (mUpgradeComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tupgrame compomemt "));

	}
}

void UGarageWidget::TestButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("WE HAVE THE UPGRADE COMPONENT"));

	//TestUpgradeButtonText->SetText(FText::FromString(TestTextWidgetString));

	mUpgradeComponent->CheckUnlock(1, 1);
}