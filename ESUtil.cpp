#include "ESUtil.h"

namespace ES
{
	int findNextSetBit(std::bitset<CAPACITY>& bitSet, size_t indexFrom)
	{
		// find the first set bit
		size_t idx = indexFrom;
		while (idx < bitSet.size() && !bitSet.test(idx))
		{
			++idx;
		}
		if (idx == bitSet.size() - 1)
		{
			return -1;
		}
		else
		{
			return idx;
		}
	}
}