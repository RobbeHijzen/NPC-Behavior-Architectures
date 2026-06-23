#include "HFSMT_BoolFunction.h"

bool HFSMT_BoolFunction::Evaluate(float deltaTime) const
{
	return _Function();
}
