#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "crafting_system_001/Scripts/Actors/ProjectileBase.h"

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
	SpawnProjectile();
}

void APawnBase::HandleDestruction()
{
	//Turret Destruction will hide the meshes (inc. disable collisions), wait a certain amount of time, then un-hide (inc. re-enable collisions).

	//hide meshes
	mBaseMesh->bHiddenInGame = true;
	mTurretMesh->bHiddenInGame = true;
	mBarrelMesh->bHiddenInGame = true;

	//disable collisions
	mBaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mTurretMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBarrelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//drop resources

	//start timer

}

void APawnBase::HandleRespawn()
{
	//show meshes
	mBaseMesh->bHiddenInGame = false;
	mTurretMesh->bHiddenInGame = false;
	mBarrelMesh->bHiddenInGame = false;

	//enable collisions
	mBaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mTurretMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mBarrelMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
}