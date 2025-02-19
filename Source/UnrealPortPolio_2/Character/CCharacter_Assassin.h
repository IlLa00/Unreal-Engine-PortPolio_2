#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CCharacter_Assassin.generated.h"

class UAttackComponent;

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

	UFUNCTION()
		void FootOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UAttackComponent* FootAttackComp;
};
