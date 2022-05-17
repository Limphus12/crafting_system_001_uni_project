#include "TankPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ResourceComponent.h"

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	InitComponents();
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

	aPlayerInputComponent->BindAxis("Vertical", this, &ATankPawn::CalculateMovementInput);
	aPlayerInputComponent->BindAxis("Horizontal", this, &ATankPawn::CalculateRotationInput);

	aPlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);

	aPlayerInputComponent->BindAction("TestA", IE_Pressed, this, &ATankPawn::AddTestResource);
	aPlayerInputComponent->BindAction("TestB", IE_Pressed, this, &ATankPawn::MinusTestResource);
}

void ATankPawn::InitComponents()
{
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

void ATankPawn::AddTestResource()
{
	if (mResourceComponent == nullptr) return;

	mResourceComponent->AddTestResource();
}

void ATankPawn::MinusTestResource()
{
	if (mResourceComponent == nullptr) return;

	mResourceComponent->MinusTestResource();
}