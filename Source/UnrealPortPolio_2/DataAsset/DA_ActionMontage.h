#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ActionMontage.generated.h"

USTRUCT(BlueprintType)
struct FActionMontage  
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<TObjectPtr<UAnimMontage>> MainAttack;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> Sub;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> Evade;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> KnockBack;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> KnockDown;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> Jump;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> JumpAttack;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> QSkill;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> ESkill;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> RSkill;
}; 



UCLASS()
class UNREALPORTPOLIO_2_API UDA_ActionMontage : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TArray<FActionMontage> Datas;
};
