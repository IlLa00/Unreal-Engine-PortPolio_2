#include "Character/Component/AttackComponent.h"
#include "Global.h"

UAttackComponent::UAttackComponent()
{
	AttackType = EAttackType::AT_Normal;
}

void UAttackComponent::SetAttackType(EAttackType NewType)
{
	AttackType = NewType;
	
	/*switch (AttackType)
	{
	case EAttackType::AT_Normal:
		PrintLine();
		break;
	case EAttackType::AT_KnockBack:
		PrintLine();
		break;
	case EAttackType::AT_Airborne:
		PrintLine();
		break;
	default:
		break;
	}*/
}
