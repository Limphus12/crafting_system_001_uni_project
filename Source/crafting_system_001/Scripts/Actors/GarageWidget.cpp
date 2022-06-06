#include "GarageWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "crafting_system_001/Scripts/Pawns/UpgradeManagerComponent.h"

class UUpgradeManagerComponent;


void UGarageWidget::NativeConstruct()
{
	/*
	if (TestUpgradeButton && TestUpgradeButtonText)
	{
		//Binding the testbuttononclicked method to the button
		//TestUpgradeButton->OnClicked.AddDynamic(this, &UGarageWidget::TestButtonOnClicked); 

		//InitUpgradeComponent();
	}
	*/

	//method bindings

	//turret
	if (TurretButtonT1) TurretButtonT1->OnClicked.AddDynamic(this, &UGarageWidget::TurretButtonT1OnClicked);
	if (TurretButtonT2) TurretButtonT2->OnClicked.AddDynamic(this, &UGarageWidget::TurretButtonT2OnClicked);
	if (TurretButtonT3) TurretButtonT3->OnClicked.AddDynamic(this, &UGarageWidget::TurretButtonT3OnClicked);

	//chassis
	if (ChassisButtonT1) ChassisButtonT1->OnClicked.AddDynamic(this, &UGarageWidget::ChassisButtonT1OnClicked);
	if (ChassisButtonT2) ChassisButtonT2->OnClicked.AddDynamic(this, &UGarageWidget::ChassisButtonT2OnClicked);
	if (ChassisButtonT3) ChassisButtonT3->OnClicked.AddDynamic(this, &UGarageWidget::ChassisButtonT3OnClicked);

	//engine
	if (EngineButtonT1) EngineButtonT1->OnClicked.AddDynamic(this, &UGarageWidget::EngineButtonT1OnClicked);
	if (EngineButtonT2) EngineButtonT2->OnClicked.AddDynamic(this, &UGarageWidget::EngineButtonT2OnClicked);
	if (EngineButtonT3) EngineButtonT3->OnClicked.AddDynamic(this, &UGarageWidget::EngineButtonT3OnClicked);
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

/*
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
*/

//selected components - value correlates to the part i.e 0 - chassis, 1 - barrel, 3 - engine


//turret
void UGarageWidget::TurretButtonT1OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Turret T1 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(1, 1); //turret (1), tier 1 (1)
	mUpgradeComponent->CheckUnlock(1, 1); //turret (1), tier 1 (1)
}
void UGarageWidget::TurretButtonT2OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Turret T2 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(1, 2); //turret (1), tier 2 (2)
	mUpgradeComponent->CheckUnlock(1, 2); //turret (1), tier 2 (2)
}
void UGarageWidget::TurretButtonT3OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Turret T3 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(1, 3); //turret (1), tier 3 (3) 
	mUpgradeComponent->CheckUnlock(1, 3); //turret (1), tier 3 (3) 
}

void UGarageWidget::ChassisButtonT1OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Chassis T1 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(0, 1); //chassis (0), tier 1 (1)
	mUpgradeComponent->CheckUnlock(0, 1); //chassis (0), tier 1 (1)
}
void UGarageWidget::ChassisButtonT2OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Chassis T2 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(0, 2); //chassis (0), tier 1 (2)
	mUpgradeComponent->CheckUnlock(0, 2); //chassis (0), tier 1 (2)
}
void UGarageWidget::ChassisButtonT3OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Chassis T3 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(0, 3); //chassis (0), tier 3 (3)
	mUpgradeComponent->CheckUnlock(0, 3); //chassis (0), tier 3 (3)
}

void UGarageWidget::EngineButtonT1OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Engine T1 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(3, 1); //engine (3), tier 1 (1)
	mUpgradeComponent->CheckUnlock(3, 1); //engine (3), tier 1 (1)
}
void UGarageWidget::EngineButtonT2OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Engine T2 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(3, 2); //engine (3), tier 2 (2)
	mUpgradeComponent->CheckUnlock(3, 2); //engine (3), tier 2 (2)
}
void UGarageWidget::EngineButtonT3OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Engine T3 Button Clicked"));

	if (mUpgradeComponent == nullptr)
	{
		return;
	}

	mUpgradeComponent->CheckUnlock(3, 3); //engine (3), tier 3 (3)
	mUpgradeComponent->CheckUnlock(3, 3); //engine (3), tier 3 (3)
}

void UGarageWidget::UpdateStatsTextBlocks(float health, float damage, float speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Stats Text"));

	//turn the floats into strings
	FString healthString = FString::SanitizeFloat(health);
	FString damageString = FString::SanitizeFloat(damage);
	FString speedString = FString::SanitizeFloat(speed);

	//add some cool text
	FString healthStatString = FString("Health - " + healthString);
	FString damageStatString = FString("Damage - " + damageString);
	FString speedStatString = FString("Speed - " + speedString);

	//set the text
	HealthStatTextBlock->SetText(FText::FromString(healthStatString));
	DamageStatTextBlock->SetText(FText::FromString(damageStatString));
	SpeedStatTextBlock->SetText(FText::FromString(speedStatString));
}

void UGarageWidget::UpdateComponentsTextBlocks(int cogs, int circuitBoards, int scrap, int armourPlates)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Components Text"));

	//turn the ints into strings
	FString cogsString = FString::FromInt(cogs);
	FString circuitBoardString = FString::FromInt(circuitBoards);
	FString scrapString = FString::FromInt(scrap);
	FString armourPlateString = FString::FromInt(armourPlates);

	//set the text
	CogText->SetText(FText::FromString(cogsString));
	CircuitBoardText->SetText(FText::FromString(circuitBoardString));
	ScrapText->SetText(FText::FromString(scrapString));
	ArmourPlateText->SetText(FText::FromString(armourPlateString));
}