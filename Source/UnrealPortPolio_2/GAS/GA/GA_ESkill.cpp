#include "GAS/GA/GA_ESkill.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_ESkill::UGA_ESkill()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.RSkill")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Cooldown.Q")));

	CHelpers::GetClass(&GEECooldown, "/Game/GAS/GameplayEffect/BP_GE_ECooldown");
	CheckNull(GEECooldown);

	CooldownGameplayEffectClass = GEECooldown;
}

void UGA_ESkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);
	
	FGameplayEffectContextHandle EffectContext = Character->GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle CooldownEffectSpec = Character->GetAbilitySystemComponent()->MakeOutgoingSpec(CooldownGameplayEffectClass, 1.0f, EffectContext);

	Character->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*CooldownEffectSpec.Data.Get());

	Character->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));

	PrintLine();

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_ESkill::EndMontage);

	AnimInstance->Montage_Play(Character->GetESkillMontage());
	AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetESkillMontage());
}

void UGA_ESkill::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
}

void UGA_ESkill::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
