#include "CPlayerController.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "Character/CCharacter_Assassin.h"
#include "Character/CCharacter_Katana.h"
#include "DataAsset/DA_CharacterAttribute.h"
#include "GAS/AttributeSet/CCharacterAttributeSet.h"
#include "GAS/GA/GA_Tag.h"

ACPlayerController::ACPlayerController()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetClass(&KatanaCharacter, "/Game/Character/Katana/BP_Katana");
	CheckNull(KatanaCharacter);

	CHelpers::GetAsset(&AttributeDataSet, "/Game/DataAsset/DA_CharacterAttribute");
	CheckNull(AttributeDataSet);
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FGameplayAbilitySpec TagAbilitySpec(UGA_Tag::StaticClass());
	ASC->GiveAbility(TagAbilitySpec);

	SpawnPlayerClass.Add(Cast<ACCharacterBase>(GetPawn()));
	SpawnPlayerClass.Add(Cast<ACCharacterBase>(KatanaCharacter->GetDefaultObject()));

	CurrentHealth.Reserve(SpawnPlayerClass.Num());

	// 초기 캐릭터 설정
	CurrentPlayer->GetPlayerAttributeSet()->SetCurrentHealth(CurrentPlayer->GetPlayerAttributeSet()->GetBaseHealth());
	CurrentPlayer->GetPlayerAttributeSet()->SetCurrentDamage(CurrentPlayer->GetPlayerAttributeSet()->GetBaseDamage());
	CurrentPlayer->GetPlayerAttributeSet()->SetCurrentDefense(CurrentPlayer->GetPlayerAttributeSet()->GetBaseDefense());
}

void ACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// 여기서 데이터에셋 값 읽기
	CurrentPlayer = Cast<ACCharacterBase>(aPawn);

	for (int32 i = 0; i < AttributeDataSet->Datas.Num(); i++)
	{
		if (i == CurrentPlayer->index)
		{
			CurrentPlayer->GetPlayerAttributeSet()->SetBaseHealth(AttributeDataSet->Datas[i].BaseHealth);
			CurrentPlayer->GetPlayerAttributeSet()->SetBaseDamage(AttributeDataSet->Datas[i].BaseDamage);
			CurrentPlayer->GetPlayerAttributeSet()->SetBaseDefense(AttributeDataSet->Datas[i].BaseDefense);

			// Current값은 생각해야됨
		}
	}

	// 클래스가 없음

	if (!SpawnPlayerClass.IsEmpty()) // 나중에 Index int변수 만들어야할듯
	{
		if (CurrentPlayer == SpawnPlayerClass[0])
			CurrentPlayer->GetPlayerAttributeSet()->SetCurrentHealth(CurrentHealth[0]);
		else if (CurrentPlayer == SpawnPlayerClass[1])
			CurrentPlayer->GetPlayerAttributeSet()->SetCurrentHealth(CurrentHealth[1]);
	}
}

void ACPlayerController::OnUnPossess()
{
	// 체력 저장
	if (CurrentPlayer == SpawnPlayerClass[0])
		CurrentHealth[0] = CurrentPlayer->GetPlayerAttributeSet()->GetCurrentHealth();
	else if (CurrentPlayer == SpawnPlayerClass[1])
		CurrentHealth[1] = CurrentPlayer->GetPlayerAttributeSet()->GetCurrentHealth();

	Super::OnUnPossess();
}

UAbilitySystemComponent* ACPlayerController::GetAbilitySystemComponent() const
{
	return ASC;
}

void ACPlayerController::Tag()
{
	FVector NewLocation = CurrentPlayer->GetActorLocation();

	CurrentPlayer->GetAbilitySystemComponent()->CancelAllAbilities();
	CurrentPlayer->GetController<ACPlayerController>()->OnUnPossess();

	CurrentPlayer->Destroy();

	FTransform TF;
	TF.SetLocation(NewLocation);
	TF.SetRotation(FQuat(FRotator(0, -40, 0)));

	ACCharacter_Katana* Katana = GetWorld()->SpawnActor<ACCharacter_Katana>(KatanaCharacter, TF);
	CheckNull(Katana);

	OnPossess(Katana);
}
