// A templated class which implements a vector container.

#pragma once
#include <cstdint>

namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* A templated implementation of a vector container.
		*/
		template <typename T>
		class Vector
		{
		private:
			/**
			* A pointer to the first item in the vector (memory chunk starts here).
			*/
			T* mFront;
			/**
			* The size of the vector, i.e. the number of items in the vector.
			*/
			std::uint32_t mSize;
			/**
			* The capacity of the vector, i.e. the number of items for which space has been reserved by the vector.
			*/
			std::uint32_t mCapacity;
		public:
			// Constructors

			/**
			* Default constructor - Initializes an empty vector container.
			*/
			Vector();
			/**
			* Copy constructor - Performs a deep copy of a vector into another.
			* @param rhs The object which has to be copied into this vector.
			*/
			Vector(const Vector& rhs);
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			~Vector();

			// Methods

			/**
			* Check whether a vector is empty.
			* @return True if the vector is empty.
			*/
			bool IsEmpty() const;
			/**
			* Get the first item in the vector container.
			* @return A reference to T, at the starting position.
			*/
			T& Front();
			/**
			* Get the first item in the vector container.
			* @return A reference to T, at the starting position.
			*/
			const T& Front() const;
			/**
			* Get the last item in the vector container.
			* @return A reference to T, at the last position.
			*/
			T& Back();
			/**
			* Get the last item in the vector container.
			* @return A reference to T, at the last position.
			*/
			const T& Back() const;
			/**
			* Get the size of the vector, i.e. the number of T items in it.
			* @return The number of items in the vector (an unsigned integer).
			*/
			std::uint32_t Size() const;
			/**
			* Get the capacity of the vector, i.e. the number of T items that can fit in the space reserved by it.
			* @return The number of T items that may fit in the vector (an unsigned integer).
			*/
			std::uint32_t Capacity() const;
			/**
			* Remove the last T item in the vector.
			*/
			void PopBack();
			/**
			* Get the T item at a specific index.
			* @param index The index from which the item has to be retrieved.
			* @return A reference to the T item which is stored at the specified index.
			*/
			T& At(std::uint32_t index) const;
			/**
			* Reserve a specific amount of memory for the vector and move its data to it.
			* @param newCapacity The amount of capacity for which the memory has to be reserved.
			*/
			void Reserve(std::uint32_t newCapacity);
			/**
			* Clears the memory associated with the vector. However the memory remains reserved, i.e. the capacity remains unchanged.
			*/
			void Clear();
			/**
			* Clears and frees the memory used by the vector. This would reset the size and capacity to 0.
			*/
			void ClearAndFree();

			// Overloaded operators

			/**
			* Assignment operator overloaded to perform a deep copy of a vector into another.
			* @param rhs The vector which has to be copied into this.
			* @return A deep copy of vector rhs.
			*/
			Vector& operator=(const Vector& rhs);
			/**
			* Overloaded subscript operator - Returns a reference to the T item at given index.
			* @param index The index of the item in the vector.
			* @return Reference to the T item in the vector.
			*/
			T& operator[](std::uint32_t index);
			/**
			* Overloaded subscript operator - Returns a reference to the item of type T at given index.
			* @param index The index of the item in the vector.
			* @return Reference to the item T in the vector.
			*/
			const T& operator[](std::uint32_t index) const;
			/**
			* An Iterator for the Vector container, each object is associated with a specific index in a specific vector.
			*/
			class Iterator
			{
				friend class Vector;
			public:
				/**
				* Default constructor - Initializes an iterator with no owning vector.
				*/
				Iterator();
				/**
				* Copy constructor - Performs a deep copy of the passed iterator object into this iterator.
				* @param rhs The iterator to copy.
				*/
				Iterator(const Iterator& rhs);
				/**
				* Assignment operator overloaded to perform a deep copy of an iterator into this iterator.
				* @param it The iterator which has to be copied.
				* @return A deep copy of iterator it.
				*/
				Iterator& operator=(const Iterator& it);
				/**
				* Compares if two iterators are associated with the same T item.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators are associated with the same T item.
				*/
				bool operator==(const Iterator& it) const;
				/**
				* Compares if two iterators aren't associated with the same T item.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators aren't associated with the same T item.
				*/
				bool operator!=(const Iterator& it) const;
				/**
				* Overloaded pre-increment operator increments the item to which it is associated with in the vector.
				* @return Iterator associated with to the next item.
				*/
				Iterator& operator++();
				/**
				* Overloaded post-increment operator increments the item to which it is associated with in the vector.
				* @return Iterator associated with to the same item.
				*/
				Iterator operator++(std::int32_t);
				/**
				* Dereference the T item data the iterator is associated with.
				* @return Item in the list referred to by the iterator(T&).
				*/
				T& operator*();
				/**
				* Dereference the T item data the iterator is associated with.
				* @return Item in the list referred to by the iterator(T&).
				*/
				const T& operator*() const;
			private:
				/**
				* A private constructor for an iterator for the vector.
				* @param offset The index offset for the item in the vector which the iterator is associated with.
				* @param ownerVector The vector with which the iterator is associated.
				*/
				Iterator(const std::uint32_t offset, const Vector* ownerVector);

				/**
				* The index position(of an item) inside the vector with which the iterator is associated.
				*/
				std::uint32_t mIndexOffset;
				/**
				* A pointer to the vector which owns this iterator.
				*/
				const Vector* mOwnerVector;
			};
			public:
				/**
				* Adds the passed T item at the end of the vector.
				* @param data T item which has to be added at the end of the vector.
				*/
				Iterator PushBack(const T& data);
				/**
				* Returns an iterator which is associated with the T item at the beginning of the vector.
				* @return Iterator associated with the first item of this vector.
				*/
				Iterator begin() const;
				/**
				* Returns an iterator which points beyond the last item in this vector, thus it isn't associated with any T item.
				* @return Iterator associated with the item location beyond the last item of this vector.
				*/
				Iterator end() const;
				/**
				* Find the passed T item in the vector.
				* @param data The T item which has to be searched in the vector.
				* @return An iterator which is associated with the searched T item. It is same as the end if the item isn't found.
				*/
				Iterator Find(const T& data) const;
				/**
				* Remove the passed T item from the vector.
				* @param data The T item which has to be removed from the vector.
				* @return True if an item was successfully removed.
				*/
				bool Remove(const T& data);
				/**
				* Remove the T items from the vector between the passed iterator.
				* @param beginIt The iterator associated with item index from where onwards items have to be removed (inclusive).
				* @param endIt The iterator associated with item index till where items have to be removed (exclusive).
				* @return True if the items were successfully removed.
				*/
				bool Remove(Iterator& beginIt, Iterator& endIt);
		};
	}
}

#include "Vector.inl"