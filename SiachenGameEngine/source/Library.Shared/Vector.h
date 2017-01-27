// A templated class which implements a vector container.

#pragma once
#include <cstdint>

// Remove - Write a Remove method that allows the removal of any element in the list. 
	// Consider including an overload of Remove that accepts first and last iterators to remove a range of contiguous elements. 
	// Should removing an element auto-shrink the vector? What impact would this have on access to the vector? What performance implications are there? 
	// Describe your implementation and its trade offs in a Canvas comment.
// Modify functions which didn't have iterator logic before

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
			* Default constructor - Initializes an empty vector object.
			*/
			Vector();
			/**
			* Copy constructor - Performs a deep copy of a vector into another.
			* @param rhs The object which has to be copied into this vector.
			*/
			Vector(const Vector& rhs);
			/**
			* Default destructor ensures that there are no memory leaks.
			*/
			~Vector();

			// Methods

			/**
			* Check whether a vector is empty.
			* @return Returns true if the vector is empty.
			*/
			bool IsEmpty() const;
			
			T& Front();
			
			const T& Front() const;
			
			T& Back();
			
			const T& Back() const;
			
			std::uint32_t Size() const;
			
			std::uint32_t Capacity() const;

			void PopBack();

			T& At(std::uint32_t index) const;
			
			void Reserve(std::uint32_t newCapacity);

			void Clear();

			void ClearAndFree();

			

			// Overloaded operators

			/**
			* Assignment operator overloaded to perform a deep copy of a vector into another.
			* @param rhs The vector which has to be copied into this.
			* @return A deep copy of vector rhs.
			*/
			Vector& operator=(const Vector& rhs);
			/**
			* Overloaded subscript operator - Returns a reference to the item of type T at given index.
			* @param index The index of the item in the vector.
			* @return Reference to the item T in the vector.
			*/
			T& operator[](std::uint32_t index);
			/**
			* Overloaded subscript operator - Returns a reference to the item of type T at given index.
			* @param index The index of the item in the vector.
			* @return Reference to the item T in the vector.
			*/
			const T& operator[](std::uint32_t index) const;
		
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
				* Compares if two iterators point to the same item.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators point to the same item.
				*/
				bool operator==(const Iterator& it) const;
				/**
				* Compares if two iterators don't point to the same item.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators don't point to the same item.
				*/
				bool operator!=(const Iterator& it) const;
				/**
				* Overloaded pre-increment operator increments the item to which it points in the vector.
				* @return Iterator pointing to the next item.
				*/
				Iterator& operator++();
				/**
				* Overloaded post-increment operator increments the item to which it points in the vector.
				* @return A copy of the iterator before it incremented.
				*/
				Iterator& operator++(std::int32_t);
				/**
				* Dereference the item data the iterator points to.
				* @return Item in the list referred to by the iterator(T&).
				*/
				T& operator*();
				/**
				* Dereference the item data the iterator points to.
				* @return Item in the list referred to by the iterator(T&).
				*/
				const T& operator*() const;
			private:
				/**
				* A constructor for an iterator for the vector.
				* @param offset The index offset for the item in the vector which the iterator points to.
				* @param ownerVector The vector with which the iterator is associated.
				*/
				Iterator(const std::uint32_t offset, const Vector* ownerVector);

				/**
				* The index position(of an item) inside the vector where this iterator points to.
				*/
				std::uint32_t mIndexOffset;
				/**
				* A pointer to the vector which owns this iterator.
				*/
				const Vector* mOwnerVector;
			};
			public:
				Iterator PushBack(const T& data);
				/**
				* Returns an iterator which points to the item at the beginning of this vector.
				* @return Iterator associated with the front item of this vector.
				*/
				Iterator begin() const;
				/**
				* Returns an iterator which points beyond the last item in this vector.
				* @return Iterator associated with the item location beyond the last item of this vector.
				*/
				Iterator end() const;

				Iterator Find(const T& data) const;

				bool Remove(const T& data);

				bool Remove(Iterator& beginIt, Iterator& endIt);

				

		};
	}
}

#include "Vector.inl"