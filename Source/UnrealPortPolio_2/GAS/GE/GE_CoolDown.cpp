#include "GAS/GE/GE_CoolDown.h"

UGE_CoolDown::UGE_CoolDown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FScalableFloat DurationValue;
	DurationValue.SetValue(3.0f);

	DurationMagnitude = DurationValue;

	// InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Cooldown.Q")));
}
