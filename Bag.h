#ifndef Bag_h__
#define Bag_h__

#include <vector>
#include <memory>
#include <utility>

using std::unique_ptr;
using std::move;

// Type T shall be move - constructible and move - assignable(or have swap defined for it, for version(2)).

namespace ES
{
	// Collection like std::vector, but does not preserve the order of its
	// entities, important for performance
	template<typename E>
	class Bag
	{
	public:
		// Constructs an empty Bag with an initial capacity of 64.
		Bag()
		{
			init(64);
		}

		// Constructs an empty Bag with the specified initial capacity.
		Bag(int capacity)
		{
			init(capacity);
		}

		// Removes the element at the specified position in this Bag. does this by
		// overwriting it was last element then removing last element
		void remove(int index)
		{
			if (index < bagSize)
			{
				std::swap(data[index], data[--bagSize]); // overwrite item to remove with last element
				data[bagSize] = nullptr; // nullptr last element
			}
		}

		// Can't return the removed object because it will be destroyed
		void removeLast()
		{
			if (bagSize > 0)
			{
				data[--bagSize] = nullptr;
			}
		}

		// Removes the first occurrence of the specified element from this Bag, if
		// it is present. If the Bag does not contain the element, it is unchanged.
		// does this by overwriting it was last element then removing last element
		bool remove(E* e)
		{
			for (int i = 0; i < bagSize; i++)
			{
				E* e2 = data[i].get();

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
				if (e == data[i].get())
				{
					return true;
				}
			}
			return false;
		}

		// Removes from this Bag all of its elements that are contained in the
		// specified Bag.
		bool removeAll(Bag<E>& bag)
		{
			bool modified = false;

			for (int i = 0; i < bag.size(); i++)
			{
				E e1 = bag.get(i);

				for (int j = 0; j < bagSize; j++)
				{
					E e2 = data[j];

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
			return data[index].get();
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
		void add(unique_ptr<E> e)
		{
			// is size greater than capacity increase capacity
			if (bagSize == data.size())
			{
				grow();
			}

			data[bagSize++] = move(e);
		}

		// Set element at specified index in the bag.
		void set(int index, unique_ptr<E> e)
		{
			if (index >= data.size())
			{
				grow(index * 2);
			}
			bagSize = index + 1;
			data[index] = move(e);
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

		void addAll(Bag<E>& items)
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

		virtual ~Bag()
		{
			// Will destroy the objects
			data.clear();
		}

		//std::vector<unique_ptr<E>>::iterator begin()
		//{
		//	return data.begin();
		//}

		//std::vector<unique_ptr<E>>::iterator end()
		//{
		//	return data.begin() + bagSize;
		//}

		//std::vector<unique_ptr<E>>::const_iterator begin() const
		//{
		//	return data.begin();
		//}

		//std::vector<unique_ptr<E>>::const_iterator end() const
		//{
		//	return data.begin() + bagSize;
		//}

	private:
		std::vector<unique_ptr<E>> data;
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