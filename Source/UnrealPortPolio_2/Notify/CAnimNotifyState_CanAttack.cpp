#include "Notify/CAnimNotifyState_CanAttack.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "Character/Component/AttackComponent.h"

UCAnimNotifyState_CanAttack::UCAnimNotifyState_CanAttack()
{
	CompName = "AttackComp";
	AttackType = EAttackType::AT_Normal;
}

void UCAnimNotifyState_CanAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	TArray<UActorComponent*> Comps = Character->GetComponentsByClass(UAttackComponent::StaticClass());

	for (const auto& Comp : Comps)
	{
		UAttackComponent* AttackComp = Cast<UAttackComponent>(Comp);
		CheckNull(AttackComp);

		if (Comp->GetName() == CompName.ToString())
		{
			AttackComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			AttackComp->SetAttackType(AttackType);
			PrintLine();
		}
	}
}

void UCAnimNotifyState_CanAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	TArray<UActorComponent*> Comps = Character->GetComponentsByClass(UAttackComponent::StaticClass());

	for (const auto& Comp : Comps)
	{
		UAttackComponent* AttackComp = Cast<UAttackComponent>(Comp);
		CheckNull(AttackComp);

		if (Comp->GetName() == CompName.ToString())
		{
			AttackComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			AttackComp->SetAttackType(EAttackType::AT_Normal);

		}
	}
}
