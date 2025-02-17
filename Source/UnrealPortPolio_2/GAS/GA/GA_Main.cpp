#include "GAS/GA/GA_Main.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Main::UGA_Main()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
}

void UGA_Main::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_Main::EndMontage);

	AnimInstance->Montage_Play(Character->GetMainAttackMontages()[0]);
	AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetMainAttackMontages()[0]);
}

void UGA_Main::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);


}

void UGA_Main::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}