#include "ResourceTriggerBox.h"
#include "DrawDebugHelpers.h"

class ATankPawn;

AResourceTriggerBox::AResourceTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AResourceTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AResourceTriggerBox::OnOverlapEnd);
}

void AResourceTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AResourceTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));

		//check if teh otehr actor is the player tank


		//if so, add some resources and delete thyself
	}
}

void AResourceTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	}
}
