#include "Character/CAIControllerBase.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIControllerBase::ACAIControllerBase()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->SetMaxAge(2.f);

	PerceptionComp->ConfigureSense(*Sight);
}

void ACAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIControllerBase::OnPerceptionUpdated);
}

void ACAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACAIControllerBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

}
