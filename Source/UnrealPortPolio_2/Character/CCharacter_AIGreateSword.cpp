#include "Character/CCharacter_AIGreateSword.h"
#include "Global.h"
#include "Character/Component/AttackComponent.h"

ACCharacter_AIGreateSword::ACCharacter_AIGreateSword()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_RPG_GreatSword/Skeletal_Meshes/SK_Frank_RPG_GreatSword");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetClass(&AnimClass, "/Game/Character/AI/ABP_GreateSword");

	AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");

	GetMesh()->SetAnimClass(AnimClass);

	CHelpers::GetClass(&AIControllerClass, "/Game/Character/AI/BP_AIControllerBase");

	index = 3;
}

void ACCharacter_AIGreateSword::BeginPlay()
{
	Super::BeginPlay();


}

void ACCharacter_AIGreateSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
