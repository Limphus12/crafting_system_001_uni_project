#include "HealthComponent.h"
#include "PawnBase.h"

class APawnBase;

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	mCurrentHealth = mMaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* aDamagedActor, float aDamage, const UDamageType* aDamageType, AController* aInstigatedBy, AActor* aDamageCauser)
{
	check(aDamagedActor != nullptr);
	check(aDamage >= 0.0f);
	check(aDamageType != nullptr);
	check(aInstigatedBy != nullptr);
	check(aDamageCauser != nullptr);

	mCurrentHealth = FMath::Clamp(mCurrentHealth - aDamage, 0.0f, mMaxHealth);

	if (mCurrentHealth <= 0.0f)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("HEALTH >= 0"));

		if (isPlayer) RespawnPlayer(aDamagedActor);

		else if (!isPlayer) RespawnTurret(aDamagedActor);
	}
}

void UHealthComponent::RespawnPlayer(AActor* actor)
{
	//teleport player back to center
	FHitResult* hr = nullptr;

	actor->SetActorLocationAndRotation(UHealthComponent::mPlayerRespawnLocation, UHealthComponent::mPlayerRespawnRotation, false, hr, ETeleportType::None);

	//remove some resources from them? as a penalty for dying - I would need to access the player's resource component.

	//Reset the player's health.
	ResetHealth();
}

void UHealthComponent::RespawnTurret(AActor* actor)
{
	//grab the APawnBase Class via Cast
	APawnBase* apb = Cast<APawnBase>(actor);

	if (apb != nullptr)
	{
		apb->HandleDestruction();
	}

	else if (apb == nullptr) UE_LOG(LogTemp, Warning, TEXT("Cannot find APawnBase on this Actor"));

	//Reset the turret's health.
	ResetHealth();
}

void UHealthComponent::ResetHealth()
{
	mCurrentHealth = mMaxHealth;
}

void UHealthComponent::SetCurrentHealth(float i)
{
	mCurrentHealth = i;
}

void UHealthComponent::SetMaxHealth(float i)
{
	mMaxHealth = i;
}

float UHealthComponent::GetCurrentHealth()
{
	return mCurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return mMaxHealth;
}