#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Jump.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UGA_Jump : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Jump();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void EndMontage(UAnimMontage* Montage, bool bInterrupted);
};
