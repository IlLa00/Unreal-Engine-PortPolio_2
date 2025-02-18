#include "Notify/CAnimNotify_Dash.h"
#include "Global.h"
#include "Character/CCharacterBase.h"

void UCAnimNotify_Dash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	Character->SetActorLocation(Character->GetActorLocation() + Character->GetActorForwardVector() * 750, true);
}
