#ifndef SystemIndexManager_h__
#define SystemIndexManager_h__

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace ES
{
	// Used to generate a unique bit for each system.
	// Only used internally in EntitySystem.
	class SystemIndexManager
	{
	public:
		static void deleteSystemIndices();

		template<typename es>
		static int getIndexFor()
		{
			return getIndexFor(std::type_index(typeid(es)));
		}

		static int getIndexFor(std::type_index type);
	private:
		static int INDEX;
		static std::unordered_map<std::type_index, int> indices;
	};
}

#endif 