#include "CCharacterBase.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/CPlayerController.h"
#include "GAS/AttributeSet/CPlayerAttributeSet.h"
#include "GAS/GA/GA_Jump.h"
#include "GAS/GA/GA_Evade.h"
#include "GAS/GA/GA_Main.h"
#include "GAS/GA/GA_Sub.h"
#include "GAS/GA/GA_Tag.h"
#include "GAS/GA/GA_QSkill.h"
#include "DataAsset/DA_ActionMontage.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetAsset(&MappingContext, "/Game/Character/InputAction/IMC");
	CheckNull(MappingContext);

	CHelpers::GetAsset(&MoveAction, "/Game/Character/InputAction/IA_Move");
	CheckNull(MoveAction);

	CHelpers::GetAsset(&LookAction, "/Game/Character/InputAction/IA_Look");
	CheckNull(LookAction);

	CHelpers::GetAsset(&SprintAction, "/Game/Character/InputAction/IA_Sprint");
	CheckNull(SprintAction);

	CHelpers::GetAsset(&JumpAction, "/Game/Character/InputAction/IA_Jump");
	CheckNull(JumpAction);

	CHelpers::GetAsset(&EvadeAction, "/Game/Character/InputAction/IA_Evade");
	CheckNull(EvadeAction);
	
	CHelpers::GetAsset(&MainAction, "/Game/Character/InputAction/IA_Main");
	CheckNull(MainAction);
	
	CHelpers::GetAsset(&SubAction, "/Game/Character/InputAction/IA_Sub");
	CheckNull(SubAction);

	CHelpers::GetAsset(&TagAction, "/Game/Character/InputAction/IA_Tag");
	CheckNull(TagAction);

	CHelpers::GetAsset(&QSkillAction, "/Game/Character/InputAction/IA_QSkill");
	CheckNull(QSkillAction);

	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CheckNull(SpringArmComp);

	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 150));
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);
	CheckNull(CameraComp);

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CHelpers::CreateSceneComponent(this, &AttackComp, "AttackComp", GetMesh());
	CheckNull(AttackComp);

	AttackComp->SetActive(false);
	
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetAsset(&ActionMontageDataAsset, "/Game/DataAsset/DA_ActionMontage");
	CheckNull(ActionMontageDataAsset);

	PlayerAttributeSet = CreateDefaultSubobject<UCPlayerAttributeSet>("AttributeSet");
	CheckNull(PlayerAttributeSet);
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			SubSystem->AddMappingContext(MappingContext, 0);
	}

	FGameplayAbilitySpec JumpAbilitySpec(UGA_Jump::StaticClass());
	ASC->GiveAbility(JumpAbilitySpec);

	FGameplayAbilitySpec EvadeAbilitySpec(UGA_Evade::StaticClass());
	ASC->GiveAbility(EvadeAbilitySpec);

	FGameplayAbilitySpec MainAbilitySpec(UGA_Main::StaticClass());
	ASC->GiveAbility(MainAbilitySpec);

	FGameplayAbilitySpec SubAbilitySpec(UGA_Sub::StaticClass());
	ASC->GiveAbility(SubAbilitySpec);

	FGameplayAbilitySpec TagAbilitySpec(UGA_Tag::StaticClass());
	ASC->GiveAbility(TagAbilitySpec);

	FGameplayAbilitySpec QSkillAbilitySpec(UGA_QSkill::StaticClass());
	ASC->GiveAbility(QSkillAbilitySpec);

	for (const auto& data : ActionMontageDataAsset->Datas[index].MainAttack)
	{
		MainAttackMontages.Add(data);
	}

	JumpMontage = ActionMontageDataAsset->Datas[index].Jump;
	EvadeMontage = ActionMontageDataAsset->Datas[index].Evade;
	SubMontage = ActionMontageDataAsset->Datas[index].Sub;
	QSkillMontage = ActionMontageDataAsset->Datas[index].QSkill;
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancendInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	CheckNull(EnhancendInputComp);

	EnhancendInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Move);
	EnhancendInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Look);
	EnhancendInputComp->BindAction(SprintAction, ETriggerEvent::Started, this, &ACCharacterBase::OnSprint);
	EnhancendInputComp->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACCharacterBase::OffSprint);
	EnhancendInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Jumping);
	EnhancendInputComp->BindAction(EvadeAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Evade);
	EnhancendInputComp->BindAction(MainAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Main);
	EnhancendInputComp->BindAction(SubAction, ETriggerEvent::Started, this, &ACCharacterBase::OnSub);
	EnhancendInputComp->BindAction(SubAction, ETriggerEvent::Completed, this, &ACCharacterBase::OffSub);
	EnhancendInputComp->BindAction(TagAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Tag);
	EnhancendInputComp->BindAction(QSkillAction, ETriggerEvent::Triggered, this, &ACCharacterBase::QSkill);
}

UAbilitySystemComponent* ACCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACCharacterBase::Move(const FInputActionValue& Value)
{
	float FowardValue = Value.Get<FVector2D>().Y;
	float SideValue = Value.Get<FVector2D>().X;

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector SideDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(FowardDirection, FowardValue);
	AddMovementInput(SideDirection, SideValue);
}

void ACCharacterBase::Look(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<FVector2D>().X);
	AddControllerPitchInput(Value.Get<FVector2D>().Y);
}

void ACCharacterBase::OnSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACCharacterBase::OffSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACCharacterBase::Jumping(const FInputActionValue& Value)
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Jump::StaticClass())->Handle);
}

void ACCharacterBase::Evade(const FInputActionValue& Value)
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Evade::StaticClass())->Handle);
}

void ACCharacterBase::Main(const FInputActionValue& Value)
{
	ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main"))); // 이건 콤보때문에 생각해야됨

	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Main::StaticClass())->Handle);
}

void ACCharacterBase::OnSub(const FInputActionValue& Value)
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Sub::StaticClass())->Handle);
}

void ACCharacterBase::OffSub(const FInputActionValue& Value)
{
	ASC->CancelAbility(ASC->FindAbilitySpecFromClass(UGA_Sub::StaticClass())->Ability);
}

void ACCharacterBase::QSkill(const FInputActionValue& Value)
{
	PrintLine();
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_QSkill::StaticClass())->Handle);
}

void ACCharacterBase::Tag()
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	CheckNull(PC);

	CLog::Print(PC->GetCurrentPlayer()->GetName());
	PC->GetCurrentPlayer()->GetAbilitySystemComponent()->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Tag::StaticClass())->Handle);
}
