#ifndef RefBag_h__
#define RefBag_h__

#include <vector>
#include <utility>

// Type T shall be move - constructible and move - assignable(or have swap defined for it, for version(2)).

namespace ES
{
	// Collection like std::vector, but does not preserve the order of its
	// entities, important for performance
	template<typename E>
	class RefBag
	{
	public:
		// Constructs an empty Bag with an initial capacity of 64.
		RefBag()
		{
			init(64);
		}

		// Constructs an empty Bag with the specified initial capacity.
		RefBag(int capacity)
		{
			init(capacity);
		}

		// Removes the element at the specified position in this Bag. does this by
		// overwriting it was last element then removing last element
		E* remove(int index)
		{
			E* result = nullptr;
			if (index >= bagSize)
			{
				result = nullptr;
			}
			else
			{
				result = data[index]; // make copy of element to remove so it can be returned
				std::swap(data[index], data[--bagSize]); // overwrite item to remove with last element
				data[bagSize] = nullptr; // nullptr last element
			}
			return result;
		}

		E* removeLast()
		{
			if (bagSize > 0)
			{
				E* e = data[--bagSize];
				data[bagSize] = nullptr;
				return e;
			}

			return nullptr;
		}

		// Removes the first occurrence of the specified element from this Bag, if
		// it is present. If the Bag does not contain the element, it is unchanged.
		// does this by overwriting it was last element then removing last element
		bool remove(E* e)
		{
			for (int i = 0; i < bagSize; i++)
			{
				E* e2 = data[i];

				if (e == e2)
				{
					std::swap(data[i], data[--bagSize]); // overwrite item to remove with last element
					data[bagSize] = nullptr; // nullptr last element
					return true;
				}
			}

			return false;
		}

		bool contains(E* e)
		{
			for (int i = 0; bagSize > i; i++)
			{
				if (e == data[i])
				{
					return true;
				}
			}
			return false;
		}

		// Removes from this Bag all of its elements that are contained in the
		// specified Bag.
		bool removeAll(RefBag<E>& bag)
		{
			bool modified = false;

			for (int i = 0; i < bag.size(); i++)
			{
				E* e1 = bag.get(i);

				for (int j = 0; j < bagSize; j++)
				{
					E* e2 = data[j];

					if (e1 == e2)
					{
						remove(j);
						j--;
						modified = true;
						break;
					}
				}
			}

			return modified;
		}

		E* get(int index)
		{
			if (index >= bagSize)
			{
				return nullptr;
			}
			return data[index];
		}

		int size()
		{
			return bagSize;
		}

		// Returns the number of elements the bag can hold without growing.
		int getCapacity()
		{
			return data.size();
		}

		bool isIndexWithinBounds(int index)
		{
			return index < getCapacity();
		}

		bool isEmpty()
		{
			return bagSize == 0;
		}

		// Adds the specified element to the end of this bag. if needed also
		// increases the capacity of the bag.
		void add(E* e)
		{
			// is size greater than capacity increase capacity
			if (bagSize == data.size())
			{
				grow();
			}

			data[bagSize++] = e;
		}

		// Set element at specified index in the bag.
		void set(int index, E* e)
		{
			if (index >= data.size())
			{
				grow(index * 2);
			}
			bagSize = index + 1;
			data[index] = e;
		}

		// will delete data
		void setToNull(int index)
		{
			if (index < data.size())
			{
				data[index] = nullptr;
			}
		}

		void ensureCapacity(int index)
		{
			if (index >= data.size())
			{
				grow(index * 2);
			}
		}

		// Removes all of the elements from this bag. The bag will be empty after
		// this call returns.
		void clear()
		{
			// nullptr all elements. Will delete the objects.
			for (int i = 0; i < bagSize; i++)
			{
				data[i] = nullptr;
			}
			bagSize = 0;
		}

		void addAll(RefBag<E>& items)
		{
			for (int i = 0; items.size() > i; i++)
			{
				add(items.get(i));
			}
		}

		// Reduces the size of the backing array to the size of the actual items.
		void shrink()
		{
			if (data.size() == bagSize)
			{
				return;
			}
			data.resize(bagSize);
		}

		virtual ~RefBag()
		{
			// Will NOT destroy the objects
			data.clear();
		}

		E** begin()
		{
			//return data.begin();
			return &data[0];
		}

		E** end()
		{
			//return data.begin() + bagSize;
			return &data[bagSize];
		}

		//std::vector<E*>::const_iterator begin() const
		//{
		//	return data.begin();
		//}

		//std::vector<E*>::const_iterator end() const
		//{
		//	return data.begin() + bagSize;
		//}

	private:
		std::vector<E*> data;
		int bagSize;
		void grow()
		{
			int newCapacity = (data.size() * 3.0f) * 0.5f + 1.0f;
			grow(newCapacity);
		}

		void grow(int newCapacity)
		{
			data.resize(newCapacity);
		}

		void init(int capacity)
		{
			data.resize(capacity);
			bagSize = 0;
		}
	};
}

#endif 