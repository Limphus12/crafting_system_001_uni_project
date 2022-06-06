#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "crafting_system_001/Scripts/Actors/ProjectileBase.h"
#include "crafting_system_001/Scripts/Actors/ResourceTriggerBox.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <crafting_system_001/Scripts/Pawns/TankPawn.h>

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitComponents();
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::RotateTurret(const FVector& aLookAtTargetLocation)
{
	const FVector startLocation = mTurretMesh->GetComponentLocation();

	//We "clean" the aLookAtTargetLocation by using the same Z coordinate of teh turret mesh, so it is going to rotate without changing the height.
	const FVector endLocation = FVector(aLookAtTargetLocation.X, aLookAtTargetLocation.Y, startLocation.Z);

	const FVector fromStartToEndVector = endLocation - startLocation;
	const FRotator rotation = fromStartToEndVector.Rotation();
	mTurretMesh->SetWorldRotation(rotation);
}

void APawnBase::Fire()
{
	if (bCanShoot)
	{
		SpawnProjectile();
	}
}

void APawnBase::HandleDestruction()
{
	//UE_LOG(LogTemp, Warning, TEXT("Calling HandleDestruction"));

	//Turret Destruction will hide the meshes (inc. disable collisions), wait a certain amount of time, then un-hide (inc. re-enable collisions).

	//Hide Actor
	SetActorHiddenInGame(true);

	//Disable Collisions
	SetActorEnableCollision(false);

	//Drop Resources
	SpawnResources();

	//Start Timer
	if (!bTimer) StartTimer();
}

void APawnBase::SpawnResources()
{
	//we're getting rid of this resource trigger box thingy, just give teh player its resources lmao.
	/*
	FVector mSpawnLocation = GetActorLocation();
	FRotator mSpawnRotation = GetActorRotation();

	AResourceTriggerBox* artb = GetWorld()->SpawnActor<AResourceTriggerBox>(mSpawnLocation, mSpawnRotation);

	if (artb != nullptr)
	{
		//artb->SetTestResourceAmount(mTestResourceAmount);
		artb->SetResourceAmounts(mResourceAmounts[0], mResourceAmounts[1], mResourceAmounts[2], mResourceAmounts[3]);
	}
	*/

	//UE_LOG(LogTemp, Warning, TEXT("attempting to spawning resources"));


	//find the player in the world
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATankPawn::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("found tank actor"));


		ATankPawn* player = Cast<ATankPawn>(FoundActors[0]);

		//if we get the player, add resources :D
		if (player != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("found player :DDDD, adding resources :D"));

			player->AddResources(mResourceAmounts[0], mResourceAmounts[1], mResourceAmounts[2], mResourceAmounts[3]);
		}
	}
	
}

void APawnBase::StartTimer()
{
	//UE_LOG(LogTemp, Warning, TEXT("Calling StartTimer"));

	bTimer = true;
}

void APawnBase::Timer(float i)
{
	//UE_LOG(LogTemp, Warning, TEXT("Calling Timer"));

	//adding on passed-through float value (deltatime)
	mTimerCount += i;

	//if the timer goes over our respawn time, call reset timer.
	if (mTimerCount >= mTimeToRespawn)
	{
		ResetTimer();
	}
}

void APawnBase::ResetTimer()
{
	//UE_LOG(LogTemp, Warning, TEXT("Calling ResetTimer"));

	bTimer = false;

	mTimerCount = 0.0f;

	HandleRespawn();
}

void APawnBase::HandleRespawn()
{
	//Un-Hide Actor
	SetActorHiddenInGame(false);

	//Re-Enable Collisions
	SetActorEnableCollision(true);
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimer) Timer(DeltaTime);
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//Initializing Components
void APawnBase::InitComponents()
{
	check(mCapsuleComponent == nullptr);
	mCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = mCapsuleComponent;

	check(mBaseMesh == nullptr);
	mBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	mBaseMesh->SetupAttachment(RootComponent);

	check(mTurretMesh == nullptr);
	mTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	mTurretMesh->SetupAttachment(mBaseMesh);

	check(mBarrelMesh == nullptr);
	mBarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	mBarrelMesh->SetupAttachment(mTurretMesh);

	check(mProjectileSpawnPoint == nullptr);
	mProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	mProjectileSpawnPoint->SetupAttachment(mBarrelMesh);
}

void APawnBase::SpawnProjectile()
{
	if (mProjectileClass.Get() == nullptr)
	{
		return;
	}

	check(mProjectileSpawnPoint != nullptr);

	const FVector spawnLocation = mProjectileSpawnPoint->GetComponentLocation();
	const FRotator spawnRotation = mProjectileSpawnPoint->GetComponentRotation();

	AProjectileBase* projectile = GetWorld()->SpawnActor<AProjectileBase>(mProjectileClass, spawnLocation, spawnRotation);

	projectile->SetOwner(this);

	projectile->SetDamage(mCurrentDamage);
}

void APawnBase::UpdateDamage(float amount)
{
	mCurrentDamage = amount;
}

float APawnBase::GetDamage()
{
	return mCurrentDamage;
}