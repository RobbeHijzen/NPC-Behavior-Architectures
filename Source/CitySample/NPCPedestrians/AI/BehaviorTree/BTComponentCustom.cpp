#include "BTComponentCustom.h"

void UBTComponentCustom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	_CurrentTickTime += DeltaTime;

	if (_CurrentTickTime >= _TickInterval)
	{
		_CurrentTickTime -= _TickInterval;

		TRACE_CPUPROFILER_EVENT_SCOPE_STR("BT_Time");

		Super::TickComponent(_TickInterval, TickType, ThisTickFunction);
	}
}
