#include "ResourceComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UResourceComponent::AddTestResource(int aAmount)
{
	if (aAmount == 0) UE_LOG(LogTemp, Warning, TEXT("adding 0 resources!!! why???"));
	
	mTestResourceCount += aAmount;

	UE_LOG(LogTemp, Warning, TEXT("added test resource"));
}

void UResourceComponent::MinusTestResource(int aAmount)
{
	if (aAmount == 0) UE_LOG(LogTemp, Warning, TEXT("minus-ing 0 resources!!! why???"));

	if ((mTestResourceCount - aAmount) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("cannot minus test resource - value would fall below 0"));
	}

	else if ((mTestResourceCount - aAmount) > 0)
	{
		mTestResourceCount -= aAmount;
		UE_LOG(LogTemp, Warning, TEXT("minus'd test resource"));
	}

	else if (mTestResourceCount <= 0) UE_LOG(LogTemp, Warning, TEXT("test resource at 0 already!"));
}