#include "Notify/CAnimNotify_Targeting.h"
#include "Global.h"
#include "Character/CCharacterBase.h"

void UCAnimNotify_Targeting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCharacterBase* Character = Cast<ACCharacterBase>(MeshComp->GetOwner());
	CheckNull(Character);

	TArray<AActor*> Ignores;

	TArray<FHitResult> HitResults;
	if (UKismetSystemLibrary::SphereTraceMultiByProfile(Character->GetWorld(), Character->GetActorLocation(), Character->GetActorLocation(), 1500.f, "Pawn", true, Ignores, EDrawDebugTrace::Persistent, HitResults, true))
	{
		for (const auto& Result : HitResults)
		{
			if (!Result.GetActor()->IsA<ACCharacterBase>())
				return;

			CLog::Print(Result.GetActor()->GetName());

			Character->SetActorRotation(FQuat(FRotator(Result.GetActor()->GetActorRotation())));
			Character->SetActorLocation((Result.GetActor()->GetActorLocation()) + (Result.GetActor()->GetActorForwardVector() * -50));
		}
	}
}
