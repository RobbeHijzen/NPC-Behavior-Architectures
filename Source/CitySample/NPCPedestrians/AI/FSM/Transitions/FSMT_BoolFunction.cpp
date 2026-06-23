#include "FSMT_BoolFunction.h"

bool FSMT_BoolFunction::Evaluate(float deltaTime) const
{
	return _Function();
}
