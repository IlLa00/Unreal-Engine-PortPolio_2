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
		TObjectPtr<UAnimMontage> Padding;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> Evade;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> Jump;
}; 



UCLASS()
class UNREALPORTPOLIO_2_API UDA_ActionMontage : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TArray<FActionMontage> Datas;
};
