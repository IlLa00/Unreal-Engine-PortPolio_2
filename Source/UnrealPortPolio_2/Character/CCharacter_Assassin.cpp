#include "CCharacter_Assassin.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Character/Component/AttackComponent.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/GA_KnockBack.h"

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

	CHelpers::CreateSceneComponent(this, &FootAttackComp, "FootAttackComp", GetMesh());
	CheckNull(FootAttackComp);
	
	FootAttackComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "foot_r");
	FootAttackComp->SetAttackType(EAttackType::AT_KnockBack);
	FootAttackComp->SetActive(false);

	GetMesh()->SetAnimClass(AnimClass);

	index = 0;
}

void ACCharacter_Assassin::BeginPlay()
{
	Super::BeginPlay();

	FootAttackComp->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter_Assassin::FootOverlap);
}

void ACCharacter_Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACCharacter_Assassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ACCharacter_Assassin::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::Overlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
}

void ACCharacter_Assassin::FootOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;

	ACCharacterBase* Character = Cast<ACCharacterBase>(OtherActor);
	CheckNull(Character);
	
	CLog::Print(Character->GetName());

	Character->LaunchCharacter(GetActorForwardVector() * 100000, false, false);
}
