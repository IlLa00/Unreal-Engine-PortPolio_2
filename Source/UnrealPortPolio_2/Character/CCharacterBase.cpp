#include "CCharacterBase.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CheckNull(SpringArmComp);

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);
	CheckNull(CameraComp);

	GetCharacterMovement()->MaxWalkSpeed = 400.f; 
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

