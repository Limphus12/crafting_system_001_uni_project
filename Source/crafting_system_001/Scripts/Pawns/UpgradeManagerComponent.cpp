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
}

// Called every frame
void UUpgradeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUpgradeManagerComponent::InitComponents()
{
	AActor* actor = GetOwner();

	check(mTankProjectile == nullptr);
	mTankProjectile = Cast<AProjectileBase>(actor);

	check(mHealthComponent == nullptr);
	mHealthComponent = Cast<UHealthComponent>(actor);

	check(mHealthComponent == nullptr);
	mTankPawn = Cast<ATankPawn>(actor);

	check(mHealthComponent == nullptr);
	mResourceComponent = Cast<UResourceComponent>(actor);
}

void UUpgradeManagerComponent::CheckUnlock(int i, int j)
{
	//check if we have unlocked the part or not.

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
}

void UUpgradeManagerComponent::CheckCost(int i, int j)
{
	//components - position in array is the resource type; 0 - cogs, 1 - circuit boards, 2 - scrap, 3 - armour plates.
	//int mResources[4] = { 0, 0, 0, 0 };

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
		}

		else if (j == 1)
		{
			if (mResourceComponent->mResources[0] >= mChassisT1Costs[0] && mResourceComponent->mResources[1] >= mChassisT1Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT1Costs[2] && mResourceComponent->mResources[3] >= mChassisT1Costs[3])
			{
				Unlock(i, j);
			}
		}

		else if (j == 2)
		{
			if (mResourceComponent->mResources[0] >= mChassisT2Costs[0] && mResourceComponent->mResources[1] >= mChassisT2Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT2Costs[2] && mResourceComponent->mResources[3] >= mChassisT2Costs[3])
			{
				Unlock(i, j);
			}
		}

		else if (j == 3)
		{
			if (mResourceComponent->mResources[0] >= mChassisT3Costs[0] && mResourceComponent->mResources[1] >= mChassisT3Costs[1] ||
				mResourceComponent->mResources[2] >= mChassisT3Costs[2] && mResourceComponent->mResources[3] >= mChassisT3Costs[3])
			{
				Unlock(i, j);
			}
		}
	}
}

void UUpgradeManagerComponent::Unlock(int i, int j)
{
	//navigate to the correct upgrade boolean

	//chassis
	if (i == 0 || bChassisUnlocks[j] == false)
	{
		bChassisUnlocks[j] = true;
	}

	//barrel
	if (i == 1 || bBarrelUnlocks[j] == false)
	{
		bBarrelUnlocks[j] = true;
	}

	//suspension
	if (i == 2 || bSuspensionUnlocks[j] == false)
	{
		bSuspensionUnlocks[j] = true;
	}

	//engine
	if (i == 3 || bEngineUnlocks[j] == false)
	{
		bEngineUnlocks[j] = true;
	}

	//now we can equip the new part
	Equip(i, j);
}

void UUpgradeManagerComponent::Equip(int i, int j)
{
	//navigate to the correct part.

	//unlock 

	//change the component mesh

	//update the stats

	//if we're changing the damage, grab the projectile class and change its damage value.
	mTankProjectile->UpdateDamage(1);

	//if we're changing the health, grab the health component and update the value
	mHealthComponent->SetMaxHealth(1);
	mHealthComponent->SetCurrentHealth(1);

	//if we're changing the speed, grab the tankpawn and change the movement speed
	mTankPawn->UpdateSpeed(1);

	//if we're changing the fuel, grab the tankpawn and change the fuel amount.
	//TBD
}

