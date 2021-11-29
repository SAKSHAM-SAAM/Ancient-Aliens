// SAKSHAM SHARMA 2021


#include "BTTask_ClearBlackboard.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboard :: UBTTask_ClearBlackboard()
{
    NodeName = TEXT ("Clear BlackBoard Value");
}
EBTNodeResult::Type UBTTask_ClearBlackboard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}