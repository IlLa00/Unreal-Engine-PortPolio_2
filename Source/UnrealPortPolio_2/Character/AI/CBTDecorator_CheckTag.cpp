#include "Character/AI/CBTDecorator_CheckTag.h"
#include "Global.h"
#include "AIController.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UCBTDecorator_CheckTag::UCBTDecorator_CheckTag()
{
	NodeName = "CheckTag";
}

bool UCBTDecorator_CheckTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACCharacterBase* AI = Cast<ACCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (AI && AI->GetAbilitySystemComponent())
		return AI->GetAbilitySystemComponent()->HasMatchingGameplayTag(GameplayTag);

	return false;
}