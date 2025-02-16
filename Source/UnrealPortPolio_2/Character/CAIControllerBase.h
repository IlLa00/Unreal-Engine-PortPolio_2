#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIControllerBase.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class UNREALPORTPOLIO_2_API ACAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIControllerBase();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UAIPerceptionComponent* PerceptionComp;

private:
	UAISenseConfig_Sight* Sight;

};
