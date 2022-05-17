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
};