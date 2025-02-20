#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_KnockDown.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UGA_KnockDown : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_KnockDown();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void EndMontage(UAnimMontage* Montage, bool bInterrupted);
};
