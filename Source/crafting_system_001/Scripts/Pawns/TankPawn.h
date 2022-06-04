#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"

//#include "Blueprint/UserWidget.h"
//#include "crafting_system_001/Scripts/Actors/GarageWidget.h"

#include "TankPawn.generated.h"

class APlayerController;
class USpringArmComponent;
class UCameraComponent;
class UResourceComponent;
class UUpgradeManagerComponent;

UCLASS()
class CRAFTING_SYSTEM_001_API ATankPawn : public APawnBase
{
	GENERATED_BODY()
	
public:
	ATankPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Resources
	//void AddTestResource(int aAmount);
	//void MinusTestResource(int aAmount);

	void AddResources(int a, int b, int c, int d);
	void MinusResources(int a, int b, int c, int d);

	void UpdateSpeed(float amount);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void BeginPlay() override;
	
	void HandleDestruction() override;

private:
	void InitComponents();
	void InitPlayerController();

	void InitGarageWidget();
	void ToggleGarageWidget();

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

	/*
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Movement",
		meta = (AllowPrivateAccess = "true"))
		float mFuelAmount = 100.0f; //fuel
	*/

	//Class References

	UResourceComponent* mResourceComponent = nullptr;
	UUpgradeManagerComponent* mUpgradeComponent = nullptr;
	
	//Widget Class to Spawn
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UGarageWidget> GarageWidgetClass;

	//Widget Instance to use as our UI
	UPROPERTY()
		class UGarageWidget* mGarageWidget = nullptr;

	bool bGarageWidget = false;
	
};