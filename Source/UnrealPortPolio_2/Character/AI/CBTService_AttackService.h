#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_AttackService.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCBTService_AttackService : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_AttackService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
