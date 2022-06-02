#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ResourceTriggerBox.generated.h"

UCLASS()
class CRAFTING_SYSTEM_001_API AResourceTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	AResourceTriggerBox();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	void SetTestResourceAmount(int aAmount);
	void SetResourceAmounts(int a, int b, int c, int d);

	//Resources
	UPROPERTY(EditAnywhere, Category = "Resources")
		int mTestResourceAmount = 0;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int mResourceAmounts[4] = { 0, 0, 0, 0 };
};