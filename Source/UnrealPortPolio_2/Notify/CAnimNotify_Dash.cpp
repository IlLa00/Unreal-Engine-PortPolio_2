#include "Notify/CAnimNotify_Dash.h"
#include "Global.h"
#include "Character/CCharacterBase.h"

void UCAnimNotify_Dash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCharacterBase* AI = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(AI);

	AI->LaunchCharacter(AI->GetActorForwardVector() * FVector(2000, 0, 0), false, false);
}
