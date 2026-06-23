#include "HFSMT_Timer.h"

bool HFSMT_Timer::Evaluate(float deltaTime) const
{
	_CurrentTime += deltaTime;
	if (_CurrentTime >= _Delay)
	{
		_CurrentTime = 0.f;
		return true;
	}

	return false;
}
