#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CCharacter_Katana.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API ACCharacter_Katana : public ACCharacterBase
{
	GENERATED_BODY()
	
public:
	ACCharacter_Katana();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
