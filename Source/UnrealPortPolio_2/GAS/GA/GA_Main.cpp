#include "GAS/GA/GA_Main.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Main::UGA_Main()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
}

void UGA_Main::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	Character->PlayAnimMontage(Character->GetMainAttackMontages()[0]);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_Main::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);


}
