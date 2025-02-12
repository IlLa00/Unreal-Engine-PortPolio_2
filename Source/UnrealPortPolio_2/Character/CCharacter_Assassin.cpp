#include "CCharacter_Assassin.h"
#include "Global.h"

ACCharacter_Assassin::ACCharacter_Assassin()
{
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Frank_Slash_Pack/Frank_Assassin/Skeletal_Meshes/SK_Frank_Assassin_SkeletalMeshes");
	CheckNull(MeshAsset);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACCharacter_Assassin::BeginPlay()
{
	Super::BeginPlay();


}

void ACCharacter_Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
