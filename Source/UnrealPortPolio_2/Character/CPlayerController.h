#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACCharacterBase;
class ACCharacter_Katana;

UCLASS()
class UNREALPORTPOLIO_2_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;

public:
	void Tag();

protected:
	TArray<ACCharacterBase*> Players;
	ACCharacterBase* CurrentPlayer;

	TSubclassOf<ACCharacter_Katana> KatanaCharacter;


};
