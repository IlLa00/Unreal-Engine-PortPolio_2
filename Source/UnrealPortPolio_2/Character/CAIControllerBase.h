#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIControllerBase.generated.h"

class UAIPerceptionComponent;

UCLASS()
class UNREALPORTPOLIO_2_API ACAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIControllerBase();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UAIPerceptionComponent* PerceptionComp;
};
