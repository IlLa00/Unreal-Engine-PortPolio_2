#include "Character/AI/CBTService_AI.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"

UCBTService_AI::UCBTService_AI()
{
	NodeName = "AIService";

	bTickIntervals = true;
}

void UCBTService_AI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetOwner());
	CheckNull(AIC);
	CheckNull(AIC->GetBlackboardComponent());

	ACCharacterBase* AICharacter = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNull(AICharacter);

	if (AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"))
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("AI.Detected")));
	}
	else
	{
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("AI.Detected")));
	}
}