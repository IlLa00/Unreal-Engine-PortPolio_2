#include "GAS/GA/GA_Sub.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Sub::UGA_Sub()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Evade")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));
}

void UGA_Sub::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub")));

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_Sub::EndMontage);

	AnimInstance->Montage_Play(Character->GetSubMontage());
	AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetSubMontage());
}

void UGA_Sub::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub")));

	Character->StopAnimMontage();
}

void UGA_Sub::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
