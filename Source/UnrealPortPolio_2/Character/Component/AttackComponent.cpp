#include "Character/Component/AttackComponent.h"

UAttackComponent::UAttackComponent()
{
	AttackType = EAttackType::AT_Normal;
}

void UAttackComponent::SetAttackType(EAttackType NewType)
{
	AttackType = NewType;
}
