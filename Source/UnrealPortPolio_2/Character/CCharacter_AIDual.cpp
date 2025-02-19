#include "Character/CCharacter_AIDual.h"
#include "Global.h"
#include "Character/Component/AttackComponent.h"

ACCharacter_AIDual::ACCharacter_AIDual()
{
	CHelpers::CreateSceneComponent(this, &OtherAttackComp, "OtherAttackComp", GetMesh());
	CheckNull(OtherAttackComp);
	
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_RPG_Dual/Skeletal_Meshes/Frank_Dual");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetClass(&AnimClass, "/Game/Character/AI/ABP_Dual");

	AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");
	OtherAttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon001");

	GetMesh()->SetAnimClass(AnimClass);

	CHelpers::GetClass(&AIControllerClass, "/Game/Character/AI/BP_AIControllerBase");

	index = 4;
}

void ACCharacter_AIDual::BeginPlay()
{
	Super::BeginPlay();
}

void ACCharacter_AIDual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
