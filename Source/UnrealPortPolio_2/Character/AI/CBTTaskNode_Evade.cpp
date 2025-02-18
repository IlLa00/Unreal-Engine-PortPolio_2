#include "Character/AI/CBTTaskNode_Evade.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_Evade.h"

UCBTTaskNode_Evade::UCBTTaskNode_Evade()
{
	NodeName = "AI Evade";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Evade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_Evade::StaticClass());

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Evade::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
