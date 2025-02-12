#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Movement")
	float Direction;
};
