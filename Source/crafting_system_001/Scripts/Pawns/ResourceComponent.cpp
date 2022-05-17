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

void UResourceComponent::AddTestResource()
{
	mTestResourceCount++;

	UE_LOG(LogTemp, Warning, TEXT("added resource"));
}

void UResourceComponent::MinusTestResource()
{
	if (mTestResourceCount > 0)
	{
		mTestResourceCount--;
		UE_LOG(LogTemp, Warning, TEXT("minus'd resource"));
	}

	else UE_LOG(LogTemp, Warning, TEXT("resource at 0 already!"));
}