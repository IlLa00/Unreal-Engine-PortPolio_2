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

	FVector Start = AICharacter->GetActorLocation();
	TArray<AActor*> Ignores;
	Ignores.Add(AICharacter);

	FHitResult HitResult;

	if(UKismetSystemLibrary::SphereTraceSingleByProfile(AICharacter->GetWorld(), Start, Start, 300.f, "AttackCollision", false, Ignores, EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		FVector fev = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"))->GetActorLocation() - AICharacter->GetActorLocation();
		fev.Normalize();
		fev *= -1;

		AICharacter->SetActorRotation(fev.ToOrientationQuat());

		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Evade")));
	}

	if (Distance < 200)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.NormalAttack")));

	}
	else if (Distance < 400)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));

	}
	else if (Distance < 750)
	{
		AICharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
	}

}
