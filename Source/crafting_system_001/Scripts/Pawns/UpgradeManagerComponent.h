#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRAFTING_SYSTEM_001_API UUpgradeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpgradeManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Button Functions

	//int i is the component/part (refer to selectedComponents comment below). int j is the tier (0 being default, 1 is first tier etc.)
	void CheckUnlock(int i, int j); 
	
	//int i is the component/part, correlating to the top-down order of the unlock booleans, int j is the tier (0 is default, 1 is first tier etc.)
	void Unlock(int i, int j);

	void Equip();

	



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//unlock booleans
	bool bChassisUnlocks[4] = { true, false, false, false };
	bool bBarrelUnlocks[4] = { true, false, false, false };
	bool bSuspensionUnlocks[4] = { true, false, false, false };
	bool bEngineUnlocks[4] = { true, false, false, false };
	bool bFuelTankUnlocks[4] = { true, false, false, false };



	//selected components - value correlates to the part i.e 0 - chassis, 1 barrel, 2 - suspension, 3 - engine, 4 - fuel tank.
	//if a value is 0, use the default i.e chassis. any higher and we'll be using the other meshs/stats.
	int selectedComponents[5] = { 0, 0, 0, 0, 0 };



	//value positions in the array correlate to the tiers of component upgrades e.g. 0 is default, 1 is the first upgrate etc.

	//health - each tier totals to { 100, 250, 500, 1000 };
	const float mChassisHealthAmounts[4] = { 90, 225, 450, 900 }; //major influence
	const float mSuspensionHealthAmounts[4] = { 10, 25, 50, 100 }; //minor influence

	//damage - enemies will be balanced around these values (subject to change).
	const float mBarrelDamageAmounts[4] = { 25, 62.5, 125, 250 }; //only influence - perhaps include tank turrets as a minor barrel damage influence?

	//speed - default value was 1000, seems to be mid-tier
	const float mEngineSpeedAmounts[4] = { 225, 450, 900, 2250 }; //major influence
	const float mSuspensionSpeedAmounts[4] = { 25, 50, 100, 250 }; //minor influence

	//fuel - currently do not know what to set these as... I mean this is only a 'if we have time' mechanic.
	const float mTankFuelAmounts[4] = { 1, 1, 1, 1 }; //major influence
	const float mEngineFuelAmounts[4] = { 1, 1, 1, 1 }; //minor influence



	//component costs - the positiion in the array correlates to the resource type e.g. 0 - cogs, 1 - circuit boards, 2 - scrap, 3 - armour plates.

	//chassis
	const int mChassisT0Costs[4] = { 0, 0, 0, 0 };
	const int mChassisT1Costs[4] = { 1, 1, 1, 1 };
	const int mChassisT2Costs[4] = { 2, 2, 2, 2 };
	const int mChassisT3Costs[4] = { 3, 3, 3, 3 };

	//barrel
	const int mBarrelT0Costs[4] = { 0, 0, 0, 0 };
	const int mBarrelT1Costs[4] = { 1, 1, 1, 1 };
	const int mBarrelT2Costs[4] = { 2, 2, 2, 2 };
	const int mBarrelT3Costs[4] = { 3, 3, 3, 3 };

	//suspension
	const int mSuspensionT0Costs[4] = { 0, 0, 0, 0 };
	const int mSuspensionT1Costs[4] = { 1, 1, 1, 1 };
	const int mSuspensionT2Costs[4] = { 2, 2, 2, 2 };
	const int mSuspensionT3Costs[4] = { 3, 3, 3, 3 };

	//engines
	const int mEngineT0Costs[4] = { 0, 0, 0, 0 };
	const int mEngineT1Costs[4] = { 1, 1, 1, 1 };
	const int mEngineT2Costs[4] = { 2, 2, 2, 2 };
	const int mEngineT3Costs[4] = { 3, 3, 3, 3 };

	//fuel tanks
	const int mFuelTankT0Costs[4] = { 0, 0, 0, 0 };
	const int mFuelTankT1Costs[4] = { 1, 1, 1, 1 };
	const int mFuelTankT2Costs[4] = { 2, 2, 2, 2 };
	const int mFuelTankT3Costs[4] = { 3, 3, 3, 3 };
};