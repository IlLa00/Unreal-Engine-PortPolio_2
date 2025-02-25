#include "GAS/GA/GA_Block.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Block::UGA_Block()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Block")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Block")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Evade")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));
}

void UGA_Block::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Block")));

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_Block::EndMontage);

	AnimInstance->Montage_Play(Character->GetBlockMontage());
	AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetBlockMontage());
}

void UGA_Block::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{

}

void UGA_Block::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Block")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
