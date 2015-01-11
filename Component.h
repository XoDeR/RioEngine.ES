#ifndef Component_h__
#define Component_h__

// All components in the system must extend this class.
namespace ES
{
	class Component
	{
	public:
		virtual ~Component() {};
	protected:
		Component() {};
	};
}

#endif 