// // A templated class which implements a vector container.

#pragma once

// Constant time methods
//
// Default constructor - Initialize an empty list, or consider providing a default capacity
// Operator [] - Return a reference to the item at the given index (Const and non-const versions)
// PopBack - Remove the last item without affecting the capacity
// IsEmpty - Return a bool indicating if vector is empty
// Front and Back - Return the item at the front and back (const and non-const versions)
// Size - Return the item count as an unsigned int
// Capacity - The number of items allowed in a container as an unsigned int
// begin - Return an iterator pointing to the first element
// end - Return an iterator NOT in the container
// 
// May run in liner time
//
// PushBack - Append given item at the end, must increase the array capacity if necessary
// Copy constructor - Deep copy
// Operator= - Deep copy
// At - Takes unsigned int index and returns a reference to the item at that index. Throw exception if the index is invalid
// Destructor - Assure there are no memory leaks
// Reserve - Take an unsigned integer indicating the capacity to reserve for the array, 
	// i.e. the number of elements allocated for the array – whether or not they are occupied.  
	// Reserve must not leak memory. If memory was previously allocated, Reserve must preserve the contents of the former array.  
	// Reserve may not delete items in the container (i.e. you must not allow a smaller capacity to shrink the array).
// Find - Take a const reference to an item and return an iterator pointing to the first item in the container that matches the argument. 
	// If no match found, return end. This must work even if the sought item is not found, and even if the list is empty.
// Clear - Empty the container
// Remove - Write a Remove method that allows the removal of any element in the list. 
	// Consider including an overload of Remove that accepts first and last iterators to remove a range of contiguous elements. 
	// Should removing an element auto-shrink the vector? What impact would this have on access to the vector? What performance implications are there? 
	// Describe your implementation and its trade offs in a Canvas comment.

// Write an embedded iterator class
// == - True if two iterators point at the same node. 
// != 
// ++ - Reassign the iterator to next node. (Prefix and postfix)
// * - Return a reference to the item contained by the node (Both const non const?)
// Copy Constructor
// =

// All methods const correct
// Unit tests
// 

namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* A templated implementation of Vector container.
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
			uint32_t mSize;
			/**
			* The capacity of the vector, i.e. the number of items for which space has been reserved by the vector.
			*/
			uint32_t mCapacity;
		public:
			Vector();
			
			T& operator[](uint32_t index);
			
			const T& operator[](uint32_t index) const;
			
			bool IsEmpty();
			
			T& Front();
			
			const T& Front() const;
			
			T& Back();
			
			const T& Back() const;
			
			uint32_t Size() const;
			
			uint32_t Capacity() const;
			
			void PushBack(const T& data);
			
			void Reserve(uint32_t newCapacity);
			
			void Clear();
		};
	}
}

#include "Vector.inl"