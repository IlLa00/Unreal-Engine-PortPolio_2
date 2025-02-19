#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "CCharacterBase.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAttackComponent;
class UAbilitySystemComponent;
class UDA_ActionMontage;
class UCPlayerAttributeSet;

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
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnSprint(const FInputActionValue& Value);
	void OffSprint(const FInputActionValue& Value);
	void Jumping(const FInputActionValue& Value);
	void Evade(const FInputActionValue& Value);
	void Main(const FInputActionValue& Value);
	void OnSub(const FInputActionValue& Value);
	void OffSub(const FInputActionValue& Value);
	void QSkill(const FInputActionValue& Value);
	void ESkill(const FInputActionValue& Value);
	void RSkill(const FInputActionValue& Value);

	virtual void Tag();

	UFUNCTION()
	void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	virtual TArray<UAnimMontage*> GetMainAttackMontages() { return MainAttackMontages; }
	virtual UAnimMontage* GetJumpMontage() { return JumpMontage; }
	virtual UAnimMontage* GetJumpAttackMontage() { return JumpAttackMontage; }
	virtual UAnimMontage* GetEvadeMontage() { return EvadeMontage; }
	virtual UAnimMontage* GetSubMontage() { return SubMontage; }
	virtual UAnimMontage* GetQSkillMontage() { return QSkillMontage; }
	virtual UAnimMontage* GetESkillMontage() { return ESkillMontage; }
	virtual UAnimMontage* GetRSkillMontage() { return RSkillMontage; }
	virtual UAnimMontage* GetKnockBackMontage() { return KnockBackMontage; }

	FORCEINLINE UCPlayerAttributeSet* GetPlayerAttributeSet() { return PlayerAttributeSet; }
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputMappingContext* MappingContext;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* MoveAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* LookAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* SprintAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* JumpAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* EvadeAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* MainAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* SubAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* TagAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* QSkillAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* ESkillAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "InputAction")
	UInputAction* RSkillAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UAttackComponent* AttackComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UCPlayerAttributeSet> PlayerAttributeSet;

protected:
	UDA_ActionMontage* ActionMontageDataAsset;

	TArray<UAnimMontage*> MainAttackMontages;
	UAnimMontage* JumpMontage;
	UAnimMontage* JumpAttackMontage;
	UAnimMontage* EvadeMontage;
	UAnimMontage* SubMontage;
	UAnimMontage* QSkillMontage;
	UAnimMontage* ESkillMontage;
	UAnimMontage* RSkillMontage;
	UAnimMontage* KnockBackMontage;

public:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
		int32 index;
};
