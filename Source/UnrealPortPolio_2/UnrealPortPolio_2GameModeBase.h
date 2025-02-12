#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealPortPolio_2GameModeBase.generated.h"

UCLASS()
class UNREALPORTPOLIO_2_API AUnrealPortPolio_2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUnrealPortPolio_2GameModeBase();

protected:
	virtual void BeginPlay() override;
};
