#include "Character/CAIControllerBase.h"
#include "Global.h"
#include "Perception/AIPerceptionComponent.h"

ACAIControllerBase::ACAIControllerBase()
{
	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComp");
	CheckNull(PerceptionComp);

}

void ACAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ACAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

}
