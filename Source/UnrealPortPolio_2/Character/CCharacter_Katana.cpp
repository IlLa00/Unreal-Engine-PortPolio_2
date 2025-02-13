#include "CCharacter_Katana.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"

ACCharacter_Katana::ACCharacter_Katana()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_RPG_Katana/Skeletal_Meshes/Frank_RPG_Katana_UE4_Sk");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetClass(&AnimClass, "/Game/Character/Katana/ABP_Katana");
	CheckNull(AnimClass);

	AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");

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
