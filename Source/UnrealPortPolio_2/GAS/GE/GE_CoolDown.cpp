#include "GAS/GE/GE_CoolDown.h"

UGE_CoolDown::UGE_CoolDown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FScalableFloat DurationValue;
	DurationValue.SetValue(3.0f);

	DurationMagnitude = DurationValue;

	/*FGameplayModifierInfo Modifier;
	Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
		UCWeaponAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCWeaponAttributeSet, CurrentDamage)
	));

	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(10.f);*/

	// Modifiers.Add(Modifier);

	//FScalableFloat DurationValue;
	//DurationValue.SetValue(3.0f);

	//DurationMagnitude = DurationValue;

	//Period = 0.0f;
	//bIsBlockingOtherAbilities = true;

	//// 쿨타임이 끝난 후 애니메이션 또는 캐릭터 능력 발동 가능하도록 설정
	//FGameplayModifierInfo CooldownModifier;
	//CooldownModifier.Attribute = UAbilitySystemComponent::GetCooldownAttribute();  // 예시 속성
	//CooldownModifier.ModifierOp = EGameplayModOp::Additive;
	//CooldownModifier.Magnitude = FGameplayEffectModifierMagnitude(0.0f);  // 쿨타임이 끝난 후 능력 발동 가능

	//Modifiers.Add(CooldownModifier);


}
