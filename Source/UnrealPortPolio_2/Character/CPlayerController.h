#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemInterface.h"
#include "CPlayerController.generated.h"

class UCPlayerAttributeSet;
class ACCharacterBase;
class ACCharacter_Katana;
class UDA_CharacterAttribute;

UCLASS()
class UNREALPORTPOLIO_2_API ACPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE ACCharacterBase* GetCurrentPlayer() { return CurrentPlayer; }

public:
	void Tag();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	TArray<ACCharacterBase*> SpawnPlayerClass;
	TSubclassOf<ACCharacter_Katana> KatanaCharacter;
	ACCharacterBase* CurrentPlayer;
	
	UDA_CharacterAttribute* AttributeDataSet;
	TArray<float> CurrentHealth;
};
