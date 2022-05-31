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
}

void UUpgradeManagerComponent::CheckUnlock(int i, int j)
{
	//check if we have unlocked the part or not.

	//if so, equip it

	//if not, check if we have enough resources to unlock it.

	//if we do, then unlock and equip it.

	//if we do not, just throw a debug error for now, later on add some UI/UX.
}

void UUpgradeManagerComponent::Unlock(int i, int j)
{
	//navigate to the correct upgrade boolean

	//int i is used to select the correct part.

	//int j is used to select the correct index in the array.

	//once we have navigated to the correct boolean set it to true.

	//now we can equip it.
}

void UUpgradeManagerComponent::Equip()
{
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