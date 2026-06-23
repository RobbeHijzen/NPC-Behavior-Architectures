#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFloatComparison : uint8
{
	Less,
	LessOrEqual,
	Equal,
	NotEqual,
	GreaterOrEqual,
	Greater
};