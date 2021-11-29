// SAKSHAM SHARMA 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UBTTask_ClearBlackboard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ClearBlackboard();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
