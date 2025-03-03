#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CharacterAttribute.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAttributeData
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
class UNREALPORTPOLIO_2_API UDA_CharacterAttribute : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FCharacterAttributeData> Datas;

};
