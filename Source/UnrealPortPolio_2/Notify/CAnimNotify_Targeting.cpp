#include "Notify/CAnimNotify_Targeting.h"
#include "Global.h"
#include "Character/CCharacterBase.h"

void UCAnimNotify_Targeting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	TArray<AActor*> Ignores;

	FHitResult HitResult;
	if (UKismetSystemLibrary::SphereTraceSingleByProfile(Character->GetWorld(), Character->GetActorLocation(), Character->GetActorLocation() + 100, 1500.f, "Pawn", false, Ignores, EDrawDebugTrace::Persistent, HitResult, true))
	{
		CLog::Print(HitResult.GetActor()->GetName());

		Character->SetActorLocation((HitResult.GetActor()->GetActorLocation()) + (HitResult.GetActor()->GetActorForwardVector() * -100));
	}
}
