#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class AProjectileBase;
class UCapsuleComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class CRAFTING_SYSTEM_001_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction();

protected:
	void BeginPlay() override;

	virtual void RotateTurret(const FVector& aLookAtTargetLocation);
	virtual void Fire();
	
	virtual void HandleRespawn();

private:
	void InitComponents();
	void SpawnProjectile();

	//General collisions for the pawn
	UPROPERTY(VisibleAnywhere, 
			BlueprintReadOnly, 
			Category = "Components",
			meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* mCapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mBaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mTurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mBarrelMesh = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
		USceneComponent* mProjectileSpawnPoint = nullptr;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Projectile Type",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> mProjectileClass;
};