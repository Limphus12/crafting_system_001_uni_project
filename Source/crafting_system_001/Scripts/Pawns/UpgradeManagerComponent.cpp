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
}

// Called every frame
void UUpgradeManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
}

