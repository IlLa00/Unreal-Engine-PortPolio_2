#include "CCharacter_Katana.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Character/Component/AttackComponent.h"

ACCharacter_Katana::ACCharacter_Katana()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_RPG_Katana/Skeletal_Meshes/Frank_RPG_Katana_UE4_Sk");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetClass(&AnimClass, "/Game/Character/Katana/ABP_Katana");

	AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");
	GuardComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");

	GetMesh()->SetAnimClass(AnimClass);

	index = 1;
}

void ACCharacter_Katana::BeginPlay()
{
	Super::BeginPlay();

}

void ACCharacter_Katana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter_Katana::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACCharacter_Katana::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Overlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void ACCharacter_Katana::GuardOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::GuardOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}