#include "CCharacter_Assassin.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"

ACCharacter_Assassin::ACCharacter_Assassin()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_Assassin/Skeletal_Meshes/SK_Frank_Assassin_SkeletalMeshes");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetClass(&AnimClass, "/Game/Character/Assassin/ABP_Assassin");
	CheckNull(AnimClass);


	AttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "R_Hand_Weapon");

	GetMesh()->SetAnimClass(AnimClass);

	index = 0;
}

void ACCharacter_Assassin::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACCharacter_Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACCharacter_Assassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
