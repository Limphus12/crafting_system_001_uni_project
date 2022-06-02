#include "ResourceTriggerBox.h"
#include "DrawDebugHelpers.h"
#include "crafting_system_001/Scripts/Pawns/TankPawn.h"

class ATankPawn;

AResourceTriggerBox::AResourceTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AResourceTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AResourceTriggerBox::OnOverlapEnd);
}

void AResourceTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	//Sizing up the actor, so that it is easier to get the resource.
	SetActorScale3D(FVector(5, 5, 5));

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AResourceTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));

		//Grab the TankPawn class, to ensure the OtherActor is the player
		ATankPawn* atp = Cast<ATankPawn>(OtherActor);

		if (atp != nullptr)
		{
			atp->AddTestResource(mTestResourceAmount);

			Destroy();
		}
	}
}

void AResourceTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	}
}

void AResourceTriggerBox::SetTestResourceAmount(int aAmount)
{
	mTestResourceAmount = aAmount;
}

void AResourceTriggerBox::SetResourceAmounts(int a, int b, int c, int d)
{
	mResourceAmounts[0] = a;
	mResourceAmounts[1] = b;
	mResourceAmounts[2] = c;
	mResourceAmounts[3] = d;
}