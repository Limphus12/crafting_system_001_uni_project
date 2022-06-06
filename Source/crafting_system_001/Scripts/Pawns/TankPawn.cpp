#include "TankPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ResourceComponent.h"

#include "Blueprint/UserWidget.h"

#include "crafting_system_001/Scripts/Pawns/UpgradeManagerComponent.h"


// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	InitComponents();

	//UI
	//GarageWidgetClass = nullptr;
	mGarageWidget = nullptr;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerController();
}

void ATankPawn::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanMove)
	{
		Move();
		RotateBody();
		RotateTurretToMouseCursorLocation();
	}
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);

	//Binding Inputs
	aPlayerInputComponent->BindAxis("Vertical", this, &ATankPawn::CalculateMovementInput);
	aPlayerInputComponent->BindAxis("Horizontal", this, &ATankPawn::CalculateRotationInput);

	aPlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);

	aPlayerInputComponent->BindAction("UI", IE_Pressed, this, &ATankPawn::ToggleGarageWidget);

	//aPlayerInputComponent->BindAction("TestA", IE_Pressed, this, &ATankPawn::AddTestResource());
	//aPlayerInputComponent->BindAction("TestB", IE_Pressed, this, &ATankPawn::MinusTestResource());
}

void ATankPawn::InitComponents()
{
	UE_LOG(LogTemp, Warning, TEXT("tank init comp"));

	check(mSpringArm == nullptr);
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	mSpringArm->SetupAttachment(RootComponent);

	check(mCamera == nullptr);
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm);

	check(mResourceComponent == nullptr);
	mResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));
}

void ATankPawn::InitPlayerController()
{
	check(mPlayerController == nullptr);

	mPlayerController = Cast<APlayerController>(GetController());
}

void ATankPawn::CalculateMovementInput(const float aValue)
{
	const float xMovement = aValue * mMovementSpeed * GetWorld()->GetDeltaSeconds();
	mMovementDirection = FVector(xMovement, 0.0f, 0.0f);
}

void ATankPawn::CalculateRotationInput(const float aValue)
{
	const float yRotation = aValue * mRotationSpeed * GetWorld()->GetDeltaSeconds();
	const FRotator rotation = FRotator(0.0f, yRotation, 0.0f);
	mRotationDirection = FQuat(rotation);
}

void ATankPawn::Move()
{
	AddActorLocalOffset(mMovementDirection, true); //Sweep
}

void ATankPawn::RotateBody()
{
	AddActorLocalRotation(mRotationDirection, true); //Sweep
}

void ATankPawn::RotateTurretToMouseCursorLocation()
{
	if (mPlayerController == nullptr)
	{
		return;
	}

	FHitResult hitResult;
	mPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);

	const FVector& hitLocation = hitResult.ImpactPoint;
	RotateTurret(hitLocation);

	//TODO - If we do not get a hitResult, the turret does not follow the mouse. So! we need to add an extra bit of code to handle that
	//I know how to do this in Unity with raycasting, so its just a matter of figuring out how to do it here...
}


void ATankPawn::ToggleGarageWidget()
{
	bGarageWidget = !bGarageWidget;
	bCanMove = !bCanMove;
	bCanShoot = !bCanShoot;

	if (bGarageWidget)
	{
		MoveToGarage();
	}

	else if (!bGarageWidget)
	{
		ReturnFromGarage();
	}
}

void ATankPawn::MoveToGarage()
{
	InitGarageWidget();
	mPlayerController->bShowMouseCursor = true;

	FHitResult* hr = nullptr;

	this->SetActorLocationAndRotation(mPlayerGarageLocation, mPlayerGarageRotation, false, hr, ETeleportType::None);
}

void ATankPawn::ReturnFromGarage()
{
	mGarageWidget->RemoveFromParent();
	mGarageWidget = nullptr;
	mPlayerController->bShowMouseCursor = false;

	FHitResult* hr = nullptr;

	this->SetActorLocationAndRotation(mPlayerReturnLocation, mPlayerReturnRotation, false, hr, ETeleportType::None);
}

void ATankPawn::InitGarageWidget()
{
	if (GarageWidgetClass)
	{
		APlayerController* apc = GetController<APlayerController>();
		check(apc);
		mGarageWidget = CreateWidget<UGarageWidget>(apc, GarageWidgetClass);
		check(mGarageWidget);
		mGarageWidget->AddToPlayerScreen();

		//moved from initcomponents(), since this is called on compile, rather than at runtime.
		if (mUpgradeComponent == nullptr)
		{
			mUpgradeComponent = this->FindComponentByClass<UUpgradeManagerComponent>();
		}

		if (mUpgradeComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Wu comp eheh :D"));
		}

		else if (mUpgradeComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nu comp wawa D:"));
		}

		mGarageWidget->InitUpgradeComponent(mUpgradeComponent);

		UpdateGarageWidgetStats();


	}
}

/*
void ATankPawn::AddTestResource(int aAmount)
{
	if (mResourceComponent == nullptr) return;

	mResourceComponent->AddTestResource(aAmount);
}

void ATankPawn::MinusTestResource(int aAmount)
{
	if (mResourceComponent == nullptr) return;

	mResourceComponent->MinusTestResource(aAmount);
}
*/

void ATankPawn::UpdateSpeed(float amount)
{
	mMovementSpeed = amount;
}

//adding resources by calling the addresource method on the resource component.
void ATankPawn::AddResources(int a, int b, int c, int d)
{
	mResourceComponent->AddResources(a, b, c, d);
}

void ATankPawn::MinusResources(int a, int b, int c, int d)
{
	mResourceComponent->MinusResources(a, b, c, d);
}

void ATankPawn::UpdateGarageWidgetStats()
{
	UHealthComponent* health = this->FindComponentByClass<UHealthComponent>();

	if (health != nullptr)
	{
		mGarageWidget->UpdateStatsTextBlocks(health->GetMaxHealth(), mCurrentDamage, mMovementSpeed);
	}

	UResourceComponent* resources = this->FindComponentByClass<UResourceComponent>();

	if (resources != nullptr)
	{
		mGarageWidget->UpdateComponentsTextBlocks(resources->mResources[0], resources->mResources[1], resources->mResources[2], resources->mResources[3]);
	}
}