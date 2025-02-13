#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	void Tag();
};
