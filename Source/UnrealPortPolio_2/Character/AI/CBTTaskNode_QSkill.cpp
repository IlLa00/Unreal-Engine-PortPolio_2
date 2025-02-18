#include "Character/AI/CBTTaskNode_QSkill.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_QSkill.h"

UCBTTaskNode_QSkill::UCBTTaskNode_QSkill()
{
	NodeName = "AI QSkill";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_QSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_QSkill::StaticClass());

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_QSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNull(AI);

	if (!AI->GetCurrentMontage())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
