#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CheckTag.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCBTDecorator_CheckTag : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UCBTDecorator_CheckTag();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
	FGameplayTag GameplayTag;
};
