#include "ProjectileBase.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InitComponents();
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	mProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::InitComponents()
{ 
	check(mProjectileMesh == nullptr);
	mProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	mProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	RootComponent = mProjectileMesh;

	check(mProjectileMovement == nullptr);
	mProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	mProjectileMovement->InitialSpeed = mMovementSpeed;
	mProjectileMovement->MaxSpeed = mMovementSpeed;
	InitialLifeSpan = mProjectileLifeSpan;
}

void AProjectileBase::OnHit(UPrimitiveComponent* aHitComponent,
	AActor* aOtherActor,
	UPrimitiveComponent* aOtherComp,
	FVector aNormalImpulse,
	const FHitResult& aHit)
{
	AActor* owner = GetOwner();
	if (owner == nullptr) return;

	check(aOtherActor != nullptr);
	if (aOtherActor != this && aOtherActor != owner)
	{
		UGameplayStatics::ApplyDamage(aOtherActor, mDamage, owner->GetInstigatorController(), this, mDamageType);

		//UE_LOG(LogTemp, Warning, TEXT("Dealt Damage"));
	}

	Destroy();
}