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

	void AddTestResource(int aAmount);
	void MinusTestResource(int aAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
