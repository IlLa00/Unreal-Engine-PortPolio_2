#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "AttackComponent.generated.h"

UENUM(BlueprintType) 
enum class EAttackType : uint8
{
    AT_Normal UMETA(DisplayName = "Normal"),  
    AT_KnockBack UMETA(DisplayName = "KnockBack"),   
    AT_KnockDown UMETA(DisplayName = "KnockDown")
};

UCLASS()
class UNREALPORTPOLIO_2_API UAttackComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
    UAttackComponent();

public:
    void SetAttackType(EAttackType NewType);

    FORCEINLINE EAttackType GetAttackType() { return AttackType; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttackType")
        EAttackType AttackType;

    EAttackType CurrentType;
};
