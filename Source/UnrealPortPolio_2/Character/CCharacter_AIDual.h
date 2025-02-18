#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CCharacter_AIDual.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API ACCharacter_AIDual : public ACCharacterBase
{
	GENERATED_BODY()
	
public:
	ACCharacter_AIDual();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UCapsuleComponent* OtherAttackComp;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
