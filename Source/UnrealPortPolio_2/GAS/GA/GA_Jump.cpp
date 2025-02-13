#include "GAS/GA/GA_Jump.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Jump::UGA_Jump()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Evade")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->Jump();
	
	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_Jump::EndMontage);

	AnimInstance->Montage_Play(Character->GetJumpMontage());
	AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetJumpMontage());
}

void UGA_Jump::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	PrintLine();

	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
