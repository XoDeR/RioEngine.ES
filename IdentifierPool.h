#ifndef IdentifierPool_h__
#define IdentifierPool_h__

#include <vector>

namespace ES
{
	// Used only internally to generate distinct ids for entities and reuse them.
	class IdentifierPool
	{
	public:
		IdentifierPool()
			: nextAvailableId(0)
		{
		}

		int checkOut()
		{
			int result = 0;
			if (ids.size() > 0) 
			{
				result = ids.back();
				ids.pop_back();
				return result;
			}
			return nextAvailableId++;
		}

		void checkIn(int id)
		{
			ids.push_back(id);
		}
	private:
		std::vector<int> ids;
		int nextAvailableId;
	};
}

#endif 