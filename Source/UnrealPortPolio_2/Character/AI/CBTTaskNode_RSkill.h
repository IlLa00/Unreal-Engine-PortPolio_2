#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_RSkill.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCBTTaskNode_RSkill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_RSkill();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
