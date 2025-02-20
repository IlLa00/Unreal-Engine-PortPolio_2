#include "CCharacterBase.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/Component/AttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/CPlayerController.h"
#include "GAS/AttributeSet/CPlayerAttributeSet.h"
#include "GAS/GA/GA_Jump.h"
#include "GAS/GA/GA_JumpAttack.h"
#include "GAS/GA/GA_Evade.h"
#include "GAS/GA/GA_Main.h"
#include "GAS/GA/GA_Guard.h"
#include "GAS/GA/GA_Tag.h"
#include "GAS/GA/GA_QSkill.h"
#include "GAS/GA/GA_ESkill.h"
#include "GAS/GA/GA_RSkill.h"
#include "GAS/GA/GA_KnockBack.h"
#include "GAS/GA/GA_KnockDown.h"
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
	
	CHelpers::GetAsset(&GuardAction, "/Game/Character/InputAction/IA_Sub");
	CheckNull(GuardAction);

	CHelpers::GetAsset(&TagAction, "/Game/Character/InputAction/IA_Tag");
	CheckNull(TagAction);

	CHelpers::GetAsset(&QSkillAction, "/Game/Character/InputAction/IA_QSkill");
	CheckNull(QSkillAction);

	CHelpers::GetAsset(&ESkillAction, "/Game/Character/InputAction/IA_ESkill");
	CheckNull(ESkillAction);

	CHelpers::GetAsset(&RSkillAction, "/Game/Character/InputAction/IA_RSkill");
	CheckNull(RSkillAction);

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

	AttackComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
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

	FGameplayAbilitySpec JumpAttackAbilitySpec(UGA_JumpAttack::StaticClass());
	ASC->GiveAbility(JumpAttackAbilitySpec);

	FGameplayAbilitySpec EvadeAbilitySpec(UGA_Evade::StaticClass());
	ASC->GiveAbility(EvadeAbilitySpec);

	FGameplayAbilitySpec MainAbilitySpec(UGA_Main::StaticClass());
	ASC->GiveAbility(MainAbilitySpec);

	FGameplayAbilitySpec GuardAbilitySpec(UGA_Guard::StaticClass());
	ASC->GiveAbility(GuardAbilitySpec);

	FGameplayAbilitySpec QSkillAbilitySpec(UGA_QSkill::StaticClass());
	ASC->GiveAbility(QSkillAbilitySpec);

	FGameplayAbilitySpec ESkillAbilitySpec(UGA_ESkill::StaticClass());
	ASC->GiveAbility(ESkillAbilitySpec);

	FGameplayAbilitySpec RSkillAbilitySpec(UGA_RSkill::StaticClass());
	ASC->GiveAbility(RSkillAbilitySpec);

	FGameplayAbilitySpec KnockBackAbilitySpec(UGA_KnockBack::StaticClass());
	ASC->GiveAbility(KnockBackAbilitySpec);

	FGameplayAbilitySpec KnockDownAbilitySpec(UGA_KnockDown::StaticClass());
	ASC->GiveAbility(KnockDownAbilitySpec);

	for (const auto& data : ActionMontageDataAsset->Datas[index].MainAttack)
	{
		MainAttackMontages.Add(data);
	}

	JumpMontage = ActionMontageDataAsset->Datas[index].Jump;
	JumpAttackMontage = ActionMontageDataAsset->Datas[index].JumpAttack;
	EvadeMontage = ActionMontageDataAsset->Datas[index].Evade;
	GuardMontage = ActionMontageDataAsset->Datas[index].Guard;
	BlockMontage = ActionMontageDataAsset->Datas[index].Block;
	QSkillMontage = ActionMontageDataAsset->Datas[index].QSkill;
	ESkillMontage = ActionMontageDataAsset->Datas[index].ESkill;
	RSkillMontage = ActionMontageDataAsset->Datas[index].RSkill;
	KnockBackMontage = ActionMontageDataAsset->Datas[index].KnockBack;
	KnockDownMontage = ActionMontageDataAsset->Datas[index].KnockDown;

	if(AttackComp)
		AttackComp->OnComponentBeginOverlap.AddDynamic(this, &ACCharacterBase::Overlap);
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main"))))
	{
		PrintLine();
		CLog::Print("Hello");
	}*/

	/*if (AttackComp)
	{
		if (AttackComp->GetAttackType() == EAttackType::AT_KnockBack && AttackComp->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics)
			PrintLine();
	}*/

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
	EnhancendInputComp->BindAction(GuardAction, ETriggerEvent::Started, this, &ACCharacterBase::OnGuard);
	EnhancendInputComp->BindAction(GuardAction, ETriggerEvent::Completed, this, &ACCharacterBase::OffGuard);
	EnhancendInputComp->BindAction(TagAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Tag);
	EnhancendInputComp->BindAction(QSkillAction, ETriggerEvent::Triggered, this, &ACCharacterBase::QSkill);
	EnhancendInputComp->BindAction(ESkillAction, ETriggerEvent::Triggered, this, &ACCharacterBase::ESkill);
	EnhancendInputComp->BindAction(RSkillAction, ETriggerEvent::Triggered, this, &ACCharacterBase::RSkill);
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
	if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump"))))
	{
		ASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Jump")));

		ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_JumpAttack::StaticClass())->Handle);
	}
	else
	{
		ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

		ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Main::StaticClass())->Handle);
	}
}

void ACCharacterBase::OnGuard(const FInputActionValue& Value)
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_Guard::StaticClass())->Handle);
}

void ACCharacterBase::OffGuard(const FInputActionValue& Value)
{
	ASC->CancelAbility(ASC->FindAbilitySpecFromClass(UGA_Guard::StaticClass())->Ability);
}

void ACCharacterBase::QSkill(const FInputActionValue& Value)
{
	PrintLine();
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_QSkill::StaticClass())->Handle);
}

void ACCharacterBase::ESkill(const FInputActionValue& Value)
{
	PrintLine();
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_ESkill::StaticClass())->Handle);
}

void ACCharacterBase::RSkill(const FInputActionValue& Value)
{
	PrintLine();
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromClass(UGA_RSkill::StaticClass())->Handle);
}

void ACCharacterBase::Tag()
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	CheckNull(PC);

	PC->GetAbilitySystemComponent()->TryActivateAbility(PC->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UGA_Tag::StaticClass())->Handle);

}

void ACCharacterBase::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;

	ACCharacterBase* Character = Cast<ACCharacterBase>(OtherActor);
	CheckNull(Character);

	switch (AttackComp->GetAttackType())
	{
	case EAttackType::AT_Normal:
		break;
	case EAttackType::AT_KnockDown:
		Character->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_KnockDown::StaticClass());
		break;
	case EAttackType::AT_KnockBack:
		Character->GetAbilitySystemComponent()->TryActivateAbilityByClass(UGA_KnockBack::StaticClass());
		break;
	default:

		break;
	}
}