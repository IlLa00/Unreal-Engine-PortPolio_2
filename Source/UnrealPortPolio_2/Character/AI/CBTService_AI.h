#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_AI.generated.h"


UCLASS()
class UNREALPORTPOLIO_2_API UCBTService_AI : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_AI();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
