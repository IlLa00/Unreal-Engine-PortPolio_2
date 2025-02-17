#include "Character/AI/CBTTaskNode_Attack.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_Main.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "AI Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNullResult(AI, EBTNodeResult::Failed);

	AI->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_Main::StaticClass());

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACCharacterBase* AI = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNull(AI);

	if (!AI->GetCurrentMontage())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
