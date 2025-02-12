#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;

UCLASS()
class UNREALPORTPOLIO_2_API ACCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;
};
