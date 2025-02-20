#include "GA_Tag.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "Character/CPlayerController.h"
#include "AbilitySystemComponent.h"

UGA_Tag::UGA_Tag()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Tag")));

	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Tag")));
	
	ConstructorHelpers::FClassFinder<UGameplayEffect> GameplayEffectClass (TEXT("/Game/GAS/GameplayEffect/GE_CoolDown"));

	CooldownGameplayEffectClass = GameplayEffectClass.Class;
}

void UGA_Tag::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PrintLine();

	ACPlayerController* PC = Cast<ACPlayerController>(ActorInfo->OwnerActor);
	CheckNull(PC);

	FTimerHandle Timer;
	PC->GetWorld()->GetTimerManager().SetTimer(Timer, this, &UGA_Tag::Cooldown, 3.0f);

	PC->Tag();
}

void UGA_Tag::Cooldown()
{
	PrintLine();

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
