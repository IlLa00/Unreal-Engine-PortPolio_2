#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CCharacter_Assassin.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API ACCharacter_Assassin : public ACCharacterBase
{
	GENERATED_BODY()
	
public:
	ACCharacter_Assassin();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
