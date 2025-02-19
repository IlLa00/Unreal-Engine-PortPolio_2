#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "AttackComponent.generated.h"

UENUM(BlueprintType) 
enum class EAttackType : uint8
{
    AT_Normal UMETA(DisplayName = "Normal"),  
    WT_Airborne UMETA(DisplayName = "Airborne"),
    WT_KnockBack UMETA(DisplayName = "KnockBack")   
};

UCLASS()
class UNREALPORTPOLIO_2_API UAttackComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
    void SetType(EAttackType NewType);

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttackType")
        EAttackType AttackType;

    EAttackType CurrentType;
};
