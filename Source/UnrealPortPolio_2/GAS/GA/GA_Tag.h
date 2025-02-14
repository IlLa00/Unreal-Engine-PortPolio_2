#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Tag.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UGA_Tag : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Tag();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void Cooldown();
};
