#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_NormalAttack.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UGA_NormalAttack : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_NormalAttack();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	void EndMontage(UAnimMontage* Montage, bool bInterrupted);
};
