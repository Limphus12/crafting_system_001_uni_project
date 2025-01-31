#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRAFTING_SYSTEM_001_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResourceComponent();

	UPROPERTY(EditAnywhere, Category = "Resources")
	int mTestResourceCount = 0;

	//components - position in array is the resource type; 0 - cogs, 1 - circuit boards, 2 - scrap, 3 - armour plates.
	int mResources[4] = { 0, 0, 0, 0 };

	void AddTestResource(int aAmount);
	void MinusTestResource(int aAmount);

	void AddResources(int a, int b, int c, int d);
	void MinusResources(int a, int b, int c, int d);

	int * GetCurrentResources();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
