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

	Move();
	RotateBody();
	RotateTurretToMouseCursorLocation();
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

	if (bGarageWidget)
	{
		InitGarageWidget();
	}

	else if (!bGarageWidget)
	{
		mGarageWidget->RemoveFromParent();
		mGarageWidget = nullptr;
	}
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
		check(mUpgradeComponent == nullptr);
		mUpgradeComponent = this->FindComponentByClass<UUpgradeManagerComponent>();

		if (mUpgradeComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Wu comp eheh"));
		}

		else if (mUpgradeComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nu comp wawa"));
		}


		mGarageWidget->InitUpgradeComponent(mUpgradeComponent);
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