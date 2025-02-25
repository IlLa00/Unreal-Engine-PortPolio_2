#include "Notify/CAnimNotifyState_Guard.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "Components/BoxComponent.h"

void UCAnimNotifyState_Guard::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	Character->GetComponentByClass<UBoxComponent>()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UCAnimNotifyState_Guard::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	Character->GetComponentByClass<UBoxComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
