#include "Character/CAnimInstance.h"
#include "Global.h"
#include "Character/CCharacterBase.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
}
