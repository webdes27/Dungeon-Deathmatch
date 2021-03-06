// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AIGlobals.h"
#include "BTTask_SetCombatState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONDEATHMATCH_API UBTTask_SetCombatState : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EAICombatState CombatState;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
