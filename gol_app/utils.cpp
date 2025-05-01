#include "utils.h"
#include <cassert>

using namespace utils;

float utils::MapRangeLinearly(float val, Range source, Range target)
{
	assert(source.start < source.end);
	assert(target.start < target.end);

	return (val - source.start) * (target.end - target.start) / (source.end - source.start) + target.start;
}
