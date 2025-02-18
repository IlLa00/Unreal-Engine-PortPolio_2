#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_MainAttack.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCBTTaskNode_MainAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_MainAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
