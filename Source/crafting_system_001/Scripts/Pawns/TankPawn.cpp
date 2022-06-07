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



	//grab all meshes that we need

	//chassis meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChassisMesh00(TEXT("StaticMesh'/Game/Models/TestModels/tank3_body.tank3_body'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChassisMesh01(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_01/Tank_01_FM.Tank_01_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChassisMesh02(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_02/Tank_02_FM.Tank_02_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChassisMesh03(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_03/Tank_03_FM.Tank_03_FM'"));

	//check if path is valid
	if (ChassisMesh00.Succeeded())
	{
		//mesh = valid path
		ChassisMeshes[0] = ChassisMesh00.Object;
	}
	if (ChassisMesh01.Succeeded())
	{
		//mesh = valid path
		ChassisMeshes[1] = ChassisMesh01.Object;
	}
	if (ChassisMesh02.Succeeded())
	{
		//mesh = valid path
		ChassisMeshes[2] = ChassisMesh02.Object;
	}
	if (ChassisMesh03.Succeeded())
	{
		//mesh = valid path
		ChassisMeshes[3] = ChassisMesh03.Object;
	}



	//turret meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh00(TEXT("StaticMesh'/Game/Models/TestModels/tank3_turret.tank3_turret'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh01(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_01/Head_01_FM.Head_01_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh02(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_02/Head_02_FM.Head_02_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh03(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_03/Head_03_FM.Head_03_FM'"));

	//check if path is valid
	if (TurretMesh00.Succeeded())
	{
		//mesh = valid path
		TurretMeshes[0] = TurretMesh00.Object;
	}
	if (TurretMesh01.Succeeded())
	{
		//mesh = valid path
		TurretMeshes[1] = TurretMesh01.Object;
	}
	if (TurretMesh02.Succeeded())
	{
		//mesh = valid path
		TurretMeshes[2] = TurretMesh02.Object;
	}
	if (TurretMesh03.Succeeded())
	{
		//mesh = valid path
		TurretMeshes[3] = TurretMesh03.Object;
	}



	//barrel meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMesh00(TEXT("StaticMesh'/Game/Models/TestModels/tank3_barrel.tank3_barrel'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMesh01(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_01/Barrel_01_FM.Barrel_01_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMesh02(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_02/Barrel_02_FM.Barrel_02_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMesh03(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_03/Barrel_03_FM.Barrel_03_FM'"));

	//check if path is valid
	if (BarrelMesh00.Succeeded())
	{
		//mesh = valid path
		BarrelMeshes[0] = BarrelMesh00.Object;
	}
	if (BarrelMesh01.Succeeded())
	{
		//mesh = valid path
		BarrelMeshes[1] = BarrelMesh01.Object;
	}
	if (BarrelMesh02.Succeeded())
	{
		//mesh = valid path
		BarrelMeshes[2] = BarrelMesh02.Object;
	}
	if (BarrelMesh03.Succeeded())
	{
		//mesh = valid path
		BarrelMeshes[3] = BarrelMesh03.Object;
	}




	//engine meshes
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineMesh00(TEXT("StaticMesh'/Game/Models/TestModels/tank3_barrel.tank3_barrel'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineMesh01(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_01/Engine_01_FM.Engine_01_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineMesh02(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_02/Engine_02_FM.Engine_02_FM'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineMesh03(TEXT("StaticMesh'/Game/Models/FM_Models/Tanks/Tank_03/Engine_03_FM.Engine_03_FM'"));

	//check if path is valid
	/*
	if (EngineMesh00.Succeeded())
	{
		//mesh = valid path
		EngineMeshes[0] = EngineMesh00.Object;
	}
	*/
	if (EngineMesh01.Succeeded())
	{
		//mesh = valid path
		EngineMeshes[1] = EngineMesh01.Object;
	}
	if (EngineMesh02.Succeeded())
	{
		//mesh = valid path
		EngineMeshes[2] = EngineMesh02.Object;
	}
	if (EngineMesh03.Succeeded())
	{
		//mesh = valid path
		EngineMeshes[3] = EngineMesh03.Object;
	}


	
	//grab all the materials that we need

	//chassis common materials
	static ConstructorHelpers::FObjectFinder<UMaterial> ChassisMaterialW(TEXT("StaticMesh'/Game/Models/Tank_Starter_Set/Textures/Wheels_High_Poly.Wheels_High_Poly'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> ChassisMaterialT(TEXT("StaticMesh'/Game/Models/Tank_Starter_Set/Textures/Threads.Threads'"));

	if (ChassisMaterialW.Succeeded() && ChassisMaterialT.Succeeded())
	{
		ChassisMaterialWheels = ChassisMaterialW.Object;
		ChassisMaterialTreads = ChassisMaterialT.Object;
	}

	//chassis t1, 2 and 3
	static ConstructorHelpers::FObjectFinder<UMaterial> ChassisMaterial01(TEXT("StaticMesh'/Game/Models/Tank_Starter_Set/Textures/Armour_01.Armour_01'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> ChassisMaterial02(TEXT("StaticMesh'/Game/Models/Tank_2nd_Slot/Textures/Armour_02.Armour_02'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> ChassisMaterial03(TEXT("StaticMesh'/Game/Models/Tank_3rd_slot/Texture_/Armour_03.Armour_03'"));

	if (ChassisMaterial01.Succeeded() && ChassisMaterial02.Succeeded() && ChassisMaterial03.Succeeded())
	{
		//mesh = valid path
		ChassisMaterials[1] = ChassisMaterial01.Object;
		ChassisMaterials[2] = ChassisMaterial02.Object;
		ChassisMaterials[3] = ChassisMaterial03.Object;
	}
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

void ATankPawn::UpdateSpeed(float amount, float amount2)
{
	mMovementSpeed = amount;
	mRotationSpeed = amount2;
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

void ATankPawn::UpdateMesh(int i, int j)
{
	//chassis
	if (i == 0)
	{
		mBaseMesh->SetStaticMesh(ChassisMeshes[j]);

		if (j == 1)
		{
			mBaseMesh->SetMaterial(0, ChassisMaterialWheels);
			mBaseMesh->SetMaterial(1, ChassisMaterialTreads);
			mBaseMesh->SetMaterial(2, ChassisMaterials[j]);
		}

		else if (j == 2 || j == 3)
		{
			mBaseMesh->SetMaterial(0, ChassisMaterials[j]);
			mBaseMesh->SetMaterial(1, ChassisMaterialWheels);
			mBaseMesh->SetMaterial(2, ChassisMaterialTreads);
		}
	}

	//turret and barrel
	if (i == 1)
	{
		mTurretMesh->SetStaticMesh(TurretMeshes[j]);
		mBarrelMesh->SetStaticMesh(BarrelMeshes[j]);
	}

	//engine
	if (i == 3)
	{
		mEngineMesh->SetStaticMesh(EngineMeshes[j]);
	}


}