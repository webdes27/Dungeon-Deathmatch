// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_MeleeComboReady.h"
#include "PlayerCharacter.h"
#include "PlayerCombatComponent.h"

#include <Components/SkeletalMeshComponent.h>


UAnimNotifyState_MeleeComboReady::UAnimNotifyState_MeleeComboReady(const FObjectInitializer& ObjectInitializer)
{

}

void UAnimNotifyState_MeleeComboReady::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (Character && Character->HasAuthority())
	{
		Character->GetCombatComponent()->ServerSetCombatState(ECombatState::ReadyToUse);
		Character->GetCombatComponent()->MulticastIncrementMeleeComboCounter();
	}
}

void UAnimNotifyState_MeleeComboReady::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (Character && Character->HasAuthority())
	{
		Character->GetCombatComponent()->MulticastClearMeleeComboCounter();
		Character->GetCombatComponent()->MulticastSetActiveMeleeComboType(EMeleeComboType::None);
	}
}

void UAnimNotifyState_MeleeComboReady::NotifyTick(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float FrameDeltaTime)
{

}
