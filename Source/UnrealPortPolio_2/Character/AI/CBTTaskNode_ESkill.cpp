#include "Character/AI/CBTTaskNode_ESkill.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_ESkill.h"

UCBTTaskNode_ESkill::UCBTTaskNode_ESkill()
{
	NodeName = "AI ESkill";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_ESkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_ESkill::StaticClass());

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_ESkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNull(AI);

	if (!AI->GetCurrentMontage())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		AI->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
	}
}
