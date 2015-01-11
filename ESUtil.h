#ifndef ESUtil_h__
#define ESUtil_h__

#include <bitset>
#include "Capacity.h"

namespace ES
{
	int findNextSetBit(std::bitset<CAPACITY>& bitSet, size_t indexFrom);
}

#endif 