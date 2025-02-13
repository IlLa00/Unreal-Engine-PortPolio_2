#include "GA_Tag.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "Character/CPlayerController.h"
#include "AbilitySystemComponent.h"

UGA_Tag::UGA_Tag()
{

}

void UGA_Tag::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	ACPlayerController* PC = Cast<ACPlayerController>(Character->GetController());
	CheckNull(PC);

	PC->Tag();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
