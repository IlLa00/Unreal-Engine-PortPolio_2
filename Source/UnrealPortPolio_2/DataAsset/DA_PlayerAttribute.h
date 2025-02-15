#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PlayerAttribute.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAttributeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float BaseHealth;

	UPROPERTY(EditAnywhere)
	float BaseDamage;

	UPROPERTY(EditAnywhere)
	float BaseDefense;
};

UCLASS()
class UNREALPORTPOLIO_2_API UDA_PlayerAttribute : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FPlayerAttributeData> Datas;

};
