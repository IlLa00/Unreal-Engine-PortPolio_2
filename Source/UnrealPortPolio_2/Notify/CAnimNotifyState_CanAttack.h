#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Character/Component/AttackComponent.h"
#include "CAnimNotifyState_CanAttack.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCAnimNotifyState_CanAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UCAnimNotifyState_CanAttack();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName CompName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType;
};
