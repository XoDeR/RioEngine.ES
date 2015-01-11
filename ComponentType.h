#ifndef ComponentType_h__
#define ComponentType_h__

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace ES
{
	class ComponentType
	{
	public:
		int getIndex();
		std::string toString();
		static void deleteComponentTypes();

		template<typename c>
		static ComponentType& getTypeFor() 
		{
			//assert((std::is_base_of<Component, c>::value == true));
			return getTypeFor(std::type_index(typeid(c)));
		}

		template<typename c>
		static int getIndexFor() 
		{
			return getTypeFor<c>().getIndex();
		}
	private:
		static ComponentType& getTypeFor(std::type_index t);

		static int INDEX;

		int index;
		std::type_index type;

		ComponentType(std::type_index type);

		static std::unordered_map<std::type_index, ComponentType*> componentTypes;
	};
}

#endif 