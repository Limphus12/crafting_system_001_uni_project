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

void UResourceComponent::AddResources(int a, int b, int c, int d)
{
	//if (a == 0) UE_LOG(LogTemp, Warning, TEXT("adding 0 'a' resources!!! why???"));

	mResources[0] += a;
	mResources[1] += b;
	mResources[2] += c;
	mResources[3] += d;
}

void UResourceComponent::MinusResources(int a, int b, int c, int d)
{
	//if (a == 0) UE_LOG(LogTemp, Warning, TEXT("minus-ing 0 'a' resources!!! why???"));

	if ((mResources[0] - a) < 0 || (mResources[1] - b) < 0 || (mResources[2] - c) < 0 || (mResources[3] - d) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("cannot minus  resource - value would fall below 0"));
	}

	if ((mResources[0] - a) >= 0)
	{
		mResources[0] -= a;
	}

	if ((mResources[1] - b) >= 0)
	{
		mResources[1] -= b;
	}

	if ((mResources[2] - c) >= 0)
	{
		mResources[2] -= c;
	}

	if ((mResources[3] - d) >= 0)
	{
		mResources[3] -= d;
	}

	else if (mTestResourceCount <= 0) UE_LOG(LogTemp, Warning, TEXT("test resource at 0 already!"));
}

int * UResourceComponent::GetCurrentResources()
{
	return mResources;
}