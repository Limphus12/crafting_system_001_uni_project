#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRAFTING_SYSTEM_001_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, Category = "Respawn")
		bool isPlayer = false;

	UPROPERTY(EditAnywhere, Category = "Respawn")
		FVector mPlayerRespawnLocation;

	UPROPERTY(EditAnywhere, Category = "Respawn")
		FQuat mPlayerRespawnRotation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* aDamagedActor, float aDamage, const UDamageType* aDamageType, AController* aInstigatedBy, AActor* aDamageCauser);
	
	void ResetHealth();

	//Set Functions

	void SetCurrentHealth(float i);

	void SetDefaultHealth(float i);



	//Respawn Functions

	void RespawnPlayer(AActor* actor);

	void RespawnTurret(AActor* actor);

private:
	UPROPERTY(EditAnywhere)
		float mDefaultHealth = 100.0f;
		float mCurrentHealth = 0.0f;
};