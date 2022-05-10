#include "CoreMinimal.h"
#include "PawnBase.h"
#include "TankPawn.generated.h"

class APlayerController;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CRAFTING_SYSTEM_001_API ATankPawn : public APawnBase
{
	GENERATED_BODY()
	
public:
	ATankPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void BeginPlay() override;

	void HandleDestruction() override;

private:
	void InitComponents();
	void InitPlayerController();

	void CalculateMovementInput(const float aValue);
	void CalculateRotationInput(const float aValue);

	void Move();
	void RotateBody();

	void RotateTurretToMouseCursorLocation();

	APlayerController* mPlayerController = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mSpringArm = nullptr;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mCamera = nullptr;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
	FVector mMovementDirection = FVector (0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
	FQuat mRotationDirection = FQuat (0.0f, 0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed = 1000.0f; //100.0f was too slow, like snail pace, so i assume it works in cm/sec

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
	float mRotationSpeed = 60.0f; //Seems to be in degrees per second.
};