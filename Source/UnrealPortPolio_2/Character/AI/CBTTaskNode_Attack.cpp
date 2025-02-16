#include "Character/AI/CBTTaskNode_Attack.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	Cast<>AIC->GetPawn()

	return EBTNodeResult::Failed;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
