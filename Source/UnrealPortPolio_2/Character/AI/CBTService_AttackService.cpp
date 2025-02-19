#include "Character/AI/CBTService_AttackService.h"
#include "Global.h"
#include "Character/CAIControllerBase.h"
#include "Character/CCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"

UCBTService_AttackService::UCBTService_AttackService()
{
	NodeName = "AI AttackService";

	bTickIntervals = true;
}

void UCBTService_AttackService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIControllerBase* AIC = Cast<ACAIControllerBase>(OwnerComp.GetOwner());
	CheckNull(AIC);
	CheckNull(AIC->GetBlackboardComponent());
	CheckNull(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	ACCharacterBase* AICharacter = Cast<ACCharacterBase>(AIC->GetPawn());
	CheckNull(AICharacter);

	float Distance = AICharacter->GetDistanceTo(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor")));
	CLog::Print(Distance);

	if (Distance < 50)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
	}
	else if (Distance < 400)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
	}
	else if (Distance < 750)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
	}
	else
	{
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
		AICharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
	}

}
