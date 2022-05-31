#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class CRAFTING_SYSTEM_001_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	void UpdateDamage(float amount);

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	void InitComponents();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* aHitComponent,
			AActor* aOtherActor, 
			UPrimitiveComponent* aOtherComp, 
			FVector aNormalImpulse, 
			const FHitResult& aHit);

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* mProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mProjectileMesh = nullptr;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Damage",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> mDamageType;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed = 1300.0f;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Damage",
		meta = (AllowPrivateAccess = "true"))
	float mDamage = 50.0f;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Life",
		meta = (AllowPrivateAccess = "true"))
	float mProjectileLifeSpan = 10.0f;
};