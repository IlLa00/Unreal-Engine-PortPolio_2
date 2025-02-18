#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_ESkill.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCBTTaskNode_ESkill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_ESkill();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
