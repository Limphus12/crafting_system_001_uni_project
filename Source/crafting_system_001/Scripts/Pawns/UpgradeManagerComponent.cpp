#include "UpgradeManagerComponent.h"

// Sets default values for this component's properties
UUpgradeManagerComponent::UUpgradeManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UUpgradeManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitComponents();

	//UI
	//GarageWidgetClass = nullptr;
	//mGarageWidget = nullptr;

	//ToggleGarageWidget();
}

// Called every frame
void UUpgradeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUpgradeManagerComponent::InitComponents()
{
	AActor* actor = GetOwner();

	//mTankProjectile = Cast<AProjectileBase>(actor);

	//removed, were gonna update damage through the tank pawn, since the projectile's damage is set when instantiated.
	//check(mTankProjectile == nullptr);
	//mTankProjectile = Cast<AProjectileBase>(actor);

	check(mTankPawn == nullptr);
	mTankPawn = Cast<ATankPawn>(actor);

	check(mHealthComponent == nullptr);
	mHealthComponent = actor->FindComponentByClass<UHealthComponent>();

	check(mResourceComponent == nullptr);
	mResourceComponent = actor->FindComponentByClass<UResourceComponent>();
}

//i = part type, j = part tier
//call this on a widget button
void UUpgradeManagerComponent::CheckUnlock(int i, int j)
{
	//check if we have unlocked the part or not.

	UE_LOG(LogTemp, Warning, TEXT("Checking Unlock"));

	//chassis
	if (i == 0)
	{
		//if not, check if we have enough resources to unlock it.
		if (bChassisUnlocks[j] == false)
		{
			CheckCost(i, j); //if we do, then unlock and equip it.

			//if we do not, just throw a debug error for now, later on add some UI/UX.
		}

		//if so, equip it
		else if (bChassisUnlocks[j] == true)
		{
			Equip(i, j);
		}
	}

	//barrel
	if (i == 1)
	{
		//if not, check if we have enough resources to unlock it.
		if (bBarrelUnlocks[j] == false)
		{
			CheckCost(i, j); //if we do, then unlock and equip it.

			//if we do not, just throw a debug error for now, later on add some UI/UX.
		}

		//if so, equip it
		else if (bBarrelUnlocks[j] == true)
		{
			Equip(i, j);
		}
	}

	//suspension
	if (i == 2)
	{
		//if not, check if we have enough resources to unlock it.
		if (bSuspensionUnlocks[j] == false)
		{
			CheckCost(i, j); //if we do, then unlock and equip it.

			//if we do not, just throw a debug error for now, later on add some UI/UX.
		}

		//if so, equip it
		else if (bSuspensionUnlocks[j] == true)
		{
			Equip(i, j);
		}
	}

	//engine
	if (i == 3)
	{
		//if not, check if we have enough resources to unlock it.
		if (bEngineUnlocks[j] == false)
		{
			CheckCost(i, j); //if we do, then unlock and equip it.

			//if we do not, just throw a debug error for now, later on add some UI/UX.
		}

		//if so, equip it
		else if (bEngineUnlocks[j] == true)
		{
			Equip(i, j);
		}
	}
}

//i = part type, j = part tier
void UUpgradeManagerComponent::CheckCost(int i, int j)
{
	UE_LOG(LogTemp, Warning, TEXT("Checking Cost"));

	//components - position in array is the resource type; 0 - cogs, 1 - circuit boards, 2 - scrap, 3 - armour plates.
	//int mResources[4] = { 0, 0, 0, 0 };

	if (mResourceComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("We do not have the resource component"));

		return;
	}

	//chassis
	if (i == 0)
	{
		//compare the chassis cost to the resourceComponent mResources.
		if (j == 0)
		{
			if (mResourceComponent->mResources[0] >= mChassisT0Costs[0] && mResourceComponent->mResources[1] >= mChassisT0Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT0Costs[2] && mResourceComponent->mResources[3] >= mChassisT0Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 1)
		{
			if (mResourceComponent->mResources[0] >= mChassisT1Costs[0] && mResourceComponent->mResources[1] >= mChassisT1Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT1Costs[2] && mResourceComponent->mResources[3] >= mChassisT1Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 2)
		{
			if (mResourceComponent->mResources[0] >= mChassisT2Costs[0] && mResourceComponent->mResources[1] >= mChassisT2Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT2Costs[2] && mResourceComponent->mResources[3] >= mChassisT2Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 3)
		{
			if (mResourceComponent->mResources[0] >= mChassisT3Costs[0] && mResourceComponent->mResources[1] >= mChassisT3Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT3Costs[2] && mResourceComponent->mResources[3] >= mChassisT3Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}
	}

	//barrel
	if (i == 1)
	{
		//compare the chassis cost to the resourceComponent mResources.
		if (j == 0)
		{
			if (mResourceComponent->mResources[0] >= mBarrelT0Costs[0] && mResourceComponent->mResources[1] >= mBarrelT0Costs[1] ||
				mResourceComponent->mResources[2] >= mBarrelT0Costs[2] && mResourceComponent->mResources[3] >= mBarrelT0Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 1)
		{
			if (mResourceComponent->mResources[0] >= mBarrelT1Costs[0] && mResourceComponent->mResources[1] >= mBarrelT1Costs[1] ||
				mResourceComponent->mResources[2] >= mBarrelT1Costs[2] && mResourceComponent->mResources[3] >= mBarrelT1Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 2)
		{
			if (mResourceComponent->mResources[0] >= mBarrelT2Costs[0] && mResourceComponent->mResources[1] >= mBarrelT2Costs[1] ||
				mResourceComponent->mResources[2] >= mBarrelT2Costs[2] && mResourceComponent->mResources[3] >= mBarrelT2Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 3)
		{
			if (mResourceComponent->mResources[0] >= mBarrelT3Costs[0] && mResourceComponent->mResources[1] >= mBarrelT3Costs[1] ||
				mResourceComponent->mResources[2] >= mBarrelT3Costs[2] && mResourceComponent->mResources[3] >= mBarrelT3Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}
	}

	//suspension
	if (i == 0)
	{
		//compare the chassis cost to the resourceComponent mResources.
		if (j == 0)
		{
			if (mResourceComponent->mResources[0] >= mSuspensionT0Costs[0] && mResourceComponent->mResources[1] >= mSuspensionT0Costs[1] ||
				mResourceComponent->mResources[2] >= mSuspensionT0Costs[2] && mResourceComponent->mResources[3] >= mSuspensionT0Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 1)
		{
			if (mResourceComponent->mResources[0] >= mSuspensionT1Costs[0] && mResourceComponent->mResources[1] >= mSuspensionT1Costs[1] ||
				mResourceComponent->mResources[2] >= mSuspensionT1Costs[2] && mResourceComponent->mResources[3] >= mSuspensionT1Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 2)
		{
			if (mResourceComponent->mResources[0] >= mSuspensionT2Costs[0] && mResourceComponent->mResources[1] >= mSuspensionT2Costs[1] ||
				mResourceComponent->mResources[2] >= mSuspensionT2Costs[2] && mResourceComponent->mResources[3] >= mSuspensionT2Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 3)
		{
			if (mResourceComponent->mResources[0] >= mSuspensionT3Costs[0] && mResourceComponent->mResources[1] >= mSuspensionT3Costs[1] ||
				mResourceComponent->mResources[2] >= mSuspensionT3Costs[2] && mResourceComponent->mResources[3] >= mSuspensionT3Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}
	}

	//engine
	if (i == 0)
	{
		//compare the chassis cost to the resourceComponent mResources.
		if (j == 0)
		{
			if (mResourceComponent->mResources[0] >= mEngineT0Costs[0] && mResourceComponent->mResources[1] >= mEngineT0Costs[1] ||
				mResourceComponent->mResources[2] >= mEngineT0Costs[2] && mResourceComponent->mResources[3] >= mEngineT0Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 1)
		{
			if (mResourceComponent->mResources[0] >= mEngineT1Costs[0] && mResourceComponent->mResources[1] >= mEngineT1Costs[1] ||
				mResourceComponent->mResources[2] >= mEngineT1Costs[2] && mResourceComponent->mResources[3] >= mEngineT1Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 2)
		{
			if (mResourceComponent->mResources[0] >= mEngineT2Costs[0] && mResourceComponent->mResources[1] >= mEngineT2Costs[1] ||
				mResourceComponent->mResources[2] >= mEngineT2Costs[2] && mResourceComponent->mResources[3] >= mEngineT2Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}

		else if (j == 3)
		{
			if (mResourceComponent->mResources[0] >= mEngineT3Costs[0] && mResourceComponent->mResources[1] >= mEngineT3Costs[1] ||
				mResourceComponent->mResources[2] >= mEngineT3Costs[2] && mResourceComponent->mResources[3] >= mEngineT3Costs[3])
			{
				Unlock(i, j);
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot Unlock"));
			}
		}
	}
}

//i = part type, j = part tier
void UUpgradeManagerComponent::Unlock(int i, int j)
{
	//navigate to the correct upgrade boolean
	UE_LOG(LogTemp, Warning, TEXT("Unlocking Part"));

	//chassis
	if (i == 0 && bChassisUnlocks[j] == false)
	{
		bChassisUnlocks[j] = true;
	}

	//barrel
	if (i == 1 && bBarrelUnlocks[j] == false)
	{
		bBarrelUnlocks[j] = true;
	}

	//suspension
	if (i == 2 && bSuspensionUnlocks[j] == false)
	{
		bSuspensionUnlocks[j] = true;
	}

	//engine
	if (i == 3 && bEngineUnlocks[j] == false)
	{
		bEngineUnlocks[j] = true;
	}

	//now we can equip the new part
	Equip(i, j);
}

//i = part type, j = part tier
void UUpgradeManagerComponent::Equip(int i, int j)
{
	UE_LOG(LogTemp, Warning, TEXT("equipping item"));


	//navigate to the correct part

	//change the component mesh

	//update the stats

	//make sure we have all the necessary parts

	if (mHealthComponent != nullptr && mTankPawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("we got all our components :D"));

		//if we're changing the health, grab the health component and update the value
		mHealthComponent->SetMaxHealth(1);
		mHealthComponent->SetCurrentHealth(1);

		//we need to grab both health values (chassis and suspension values).

		//if we're changing the speed, grab the tankpawn and change the movement speed
		mTankPawn->UpdateSpeed(1);

		//we need to grab both speed values (engine and suspension values).

		//if we're changing the damage, grab the tankpawn class and change its damage value.
		mTankPawn->UpdateDamage(1);

		//if we're changing the fuel, grab the tankpawn and change the fuel amount.
		//TBD
	}

	//if (mTankProjectile == nullptr) UE_LOG(LogTemp, Warning, TEXT("missing projectile, baka"));
	if (mHealthComponent == nullptr) UE_LOG(LogTemp, Warning, TEXT("missing health, baka"));
	if (mTankPawn == nullptr) UE_LOG(LogTemp, Warning, TEXT("missing tank, baka"));
}

/*
void UUpgradeManagerComponent::InitGarageWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Init Garage Widget"));

	if (GarageWidgetClass)
	{
		APlayerController* apc = mTankPawn->GetController<APlayerController>();
		check(apc);
		mGarageWidget = CreateWidget<UGarageWidget>(apc, GarageWidgetClass);
		check(mGarageWidget);
		mGarageWidget->AddToPlayerScreen();

		mGarageWidget->InitUpgradeComponent(this);
	}
}

void UUpgradeManagerComponent::ToggleGarageWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Toggling Garage Widget"));

	bGarageWidget = !bGarageWidget;

	if (bGarageWidget)
	{
		InitGarageWidget();
	}

	else if (!bGarageWidget)
	{
		mGarageWidget->RemoveFromParent();
		mGarageWidget = nullptr;
	}
}
*/