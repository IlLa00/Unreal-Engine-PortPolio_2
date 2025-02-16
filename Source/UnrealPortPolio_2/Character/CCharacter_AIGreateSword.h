#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CCharacter_AIGreateSword.generated.h"


UCLASS()
class UNREALPORTPOLIO_2_API ACCharacter_AIGreateSword : public ACCharacterBase
{
	GENERATED_BODY()
	
public:
	ACCharacter_AIGreateSword();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
