#include "GarageWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGarageWidget::NativeConstruct()
{
	if (TestUpgradeButton && TestUpgradeButtonText)
	{
		//Binding the testbuttononclicked method to the button
		TestUpgradeButton->OnClicked.AddDynamic(this, &UGarageWidget::TestButtonOnClicked); 

		InitComponents();
	}
}

void UGarageWidget::InitComponents()
{
	//check(mUpgradeComponent == nullptr);

}

void UGarageWidget::TestButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Button Clicked"));

	//TestUpgradeButtonText->SetText(FText::FromString(TestTextWidgetString));


}