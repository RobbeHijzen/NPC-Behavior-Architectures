#include "STC_RandomChance.h"
#include "StateTreeExecutionContext.h"

bool FSTC_RandomChance::TestCondition(FStateTreeExecutionContext& Context) const
{
	FRandomChanceInstanceData& data = Context.GetInstanceData(*this);

	return FMath::FRand() < data.ChancePerSecond * 0.25f;
}
