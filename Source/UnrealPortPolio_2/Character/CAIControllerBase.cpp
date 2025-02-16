#include "Character/CAIControllerBase.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/CCharacterBase.h"
#include "Character/CPlayerController.h"

ACAIControllerBase::ACAIControllerBase()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	CheckNull(Sight);

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1000.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->SetMaxAge(2.f);

	PerceptionComp->ConfigureSense(*Sight);

	CHelpers::GetAsset(&BTAsset, "/Game/Character/AI/BT_AI");
	CheckNull(BTAsset);
}

void ACAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIControllerBase::OnPerceptionUpdated);

	RunBehaviorTree(BTAsset);
}

void ACAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACAIControllerBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;
	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	for (const auto& Actor : PerceivedActors)
	{
		if (Cast<ACCharacterBase>(Actor)->GetController()->IsA<ACPlayerController>())
		{
			if(GetBlackboardComponent())
				GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);

			CLog::Print(Actor->GetName());
		}
	}
}
