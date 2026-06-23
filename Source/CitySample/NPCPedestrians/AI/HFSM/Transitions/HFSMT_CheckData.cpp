#include "HFSMT_CheckData.h"

bool HFSMT_CheckData::Evaluate(float deltaTime) const
{
    float left{ _Pedestrian->GetData(_DataName) };

    switch (_Operation)
    {
    case EFloatComparison::Less:
        return left < _RightValue;

    case EFloatComparison::LessOrEqual:
        return left <= _RightValue;

    case EFloatComparison::Equal:
        return left == _RightValue;

    case EFloatComparison::NotEqual:
        return left != _RightValue;

    case EFloatComparison::GreaterOrEqual:
        return left >= _RightValue;

    case EFloatComparison::Greater:
        return left > _RightValue;

    default:
        return false;
    }
}