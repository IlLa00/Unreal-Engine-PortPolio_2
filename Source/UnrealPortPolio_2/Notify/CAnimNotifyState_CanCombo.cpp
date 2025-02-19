#include "Notify/CAnimNotifyState_CanCombo.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_Main.h"

void UCAnimNotifyState_CanCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	if(Character->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main"))))
	{
		Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
	}
}

void UCAnimNotifyState_CanCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	if (!Character->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main"))))
	{
		Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
	}
}
