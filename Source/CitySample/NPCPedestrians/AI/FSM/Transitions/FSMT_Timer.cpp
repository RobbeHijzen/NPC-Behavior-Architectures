#include "FSMT_Timer.h"

bool FSMT_Timer::Evaluate(float deltaTime) const
{
	_CurrentTime += deltaTime;
	if (_CurrentTime >= _Delay)
	{
		_CurrentTime = 0.f;
		return true;
	}

	return false;
}
