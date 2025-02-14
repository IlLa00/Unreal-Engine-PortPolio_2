#include "CPlayerController.h"
#include "Global.h"
#include "Character/CCharacter_Assassin.h"
#include "Character/CCharacter_Katana.h"

ACPlayerController::ACPlayerController()
{
	CHelpers::GetClass(&KatanaCharacter, "/Game/Character/Katana/BP_Katana");
	CheckNull(KatanaCharacter);
}

void ACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);;

	CurrentPlayer = Cast<ACCharacterBase>(aPawn);
}

void ACPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Players.Add(Cast<ACCharacterBase>(GetCharacter()));
	
	FTransform TF;
	TF.SetLocation(FVector(0, 0, 1000));
	TF.SetRotation(FQuat(FRotator()));
	Players.Add(GetWorld()->SpawnActor<ACCharacter_Katana>(KatanaCharacter, TF));


}

void ACPlayerController::Tag()
{
	OnUnPossess();

	ACCharacterBase* NewCharacter = nullptr;
	int32 Newindex = (CurrentPlayer->index) + 1;

	if (Players[Newindex])
	{
		NewCharacter = Players[Newindex];
	}
	else
	{
		Newindex = 0;
		NewCharacter = Players[Newindex];
	}

	OnPossess(NewCharacter);
}
