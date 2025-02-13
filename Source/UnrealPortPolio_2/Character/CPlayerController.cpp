#include "CPlayerController.h"
#include "Global.h"

ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

}

void ACPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACPlayerController::Tag()
{
	OnUnPossess();


}
