#include "UnrealPortPolio_2GameModeBase.h"
#include "AbilitySystemGlobals.h"
#include "Global.h"
#include "Character/CCharacter_Assassin.h"
#include "Character/CPlayerController.h"

AUnrealPortPolio_2GameModeBase::AUnrealPortPolio_2GameModeBase()
{
	UAbilitySystemGlobals::Get().InitGlobalData();

	TSubclassOf<ACCharacter_Assassin> PlayerClass;
	CHelpers::GetClass(&PlayerClass, "/Game/Character/Assassin/BP_Assassin");
	CheckNull(PlayerClass);

	DefaultPawnClass = PlayerClass;

	TSubclassOf<ACPlayerController> PlayerController;
	CHelpers::GetClass(&PlayerController, "/Game/Character/BP_CPlayerController");
	CheckNull(PlayerController);

	PlayerControllerClass = PlayerController;
}

void AUnrealPortPolio_2GameModeBase::BeginPlay()
{
	Super::BeginPlay();



}
