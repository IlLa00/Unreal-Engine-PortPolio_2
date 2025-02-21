#include "GAS/GA/GA_Main.h"
#include "Global.h"
#include "Character/CCharacterBase.h"
#include "AbilitySystemComponent.h"

UGA_Main::UGA_Main()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	// BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.QSkill")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.ESkill")));
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.RSkill")));
}

void UGA_Main::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACCharacterBase* Character = Cast<ACCharacterBase>(ActorInfo->OwnerActor);
	CheckNull(Character);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	FOnMontageEnded OnMontageEndDelegate;
	OnMontageEndDelegate.BindUObject(this, &UGA_Main::EndMontage);

	if (AnimInstance->GetCurrentActiveMontage() == Character->GetMainAttackMontages()[0])
	{
		PrintLine();
		OnMontageEndDelegate.BindUObject(this, &UGA_Main::WaitMontage);
		AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetMainAttackMontages()[0]);
	}
	else if (AnimInstance->GetCurrentActiveMontage() == Character->GetMainAttackMontages()[1])
	{
		PrintLine();
		OnMontageEndDelegate.BindUObject(this, &UGA_Main::WaitMontage);
		AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetMainAttackMontages()[1]);
	}
	else
	{
		PrintLine();
		AnimInstance->Montage_Play(Character->GetMainAttackMontages()[0]);
		AnimInstance->Montage_SetEndDelegate(OnMontageEndDelegate, Character->GetMainAttackMontages()[0]);
	}
	

	StartTimer();
}

void UGA_Main::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);


}

void UGA_Main::EndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	//ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	//CheckNull(Character);

	//Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	//EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_Main::WaitMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->OwnerActor);
	CheckNull(Character);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	CheckNull(AnimInstance);

	if(Montage == Character->GetMainAttackMontages()[0])
		AnimInstance->Montage_Play(Character->GetMainAttackMontages()[1]);
	else if((Montage == Character->GetMainAttackMontages()[1]))
		AnimInstance->Montage_Play(Character->GetMainAttackMontages()[2]);
}

void UGA_Main::StartTimer()
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->AvatarActor);
	CheckNull(Character);

	Character->GetWorld()->GetTimerManager().SetTimer(ComboTimer, this, &UGA_Main::ResetTimer, Character->GetCurrentMontage()->GetPlayLength());
}

void UGA_Main::ResetTimer()
{
	ACCharacterBase* Character = Cast<ACCharacterBase>(GetCurrentActorInfo()->AvatarActor);
	CheckNull(Character);

	Character->GetWorld()->GetTimerManager().ClearTimer(ComboTimer);

	Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Main")));

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
