// A templated class which implements a singly - linked list.

#pragma once
#include "pch.h"

namespace SiachenGameEngine
{
	/**
	* A templated class which implements a singly-linked list.
	*/
	template <typename T>
	class SList
	{
	private:
		struct Node
		{
			Node* nextNode;
			T value;
		};

		Node* m_pFront;
		Node* m_pBack;

		int32_t m_iSize;

	public:
		/**
		* Default constructor - Initializes an empty list.
		*/
		SList();
		/**
		* Copy constructor - Performs a deep copy of the passed list object into this list object.
		*/
		SList(const SList &list);
		/**
		* Destructor - Deallocates all the dynamically allocated list nodes.
		*/
		~SList();
		/**
		* Inserts an item at the front of the list.
		* @param obj The item to insert at the front.
		* @see PushBack()
		*/
		void PushFront(const T& obj);
		/**
		* Inserts an item at the back of the list.
		* @param obj The item to insert at the back.
		* @see PushFront()
		*/
		void PushBack(const T& obj);
		/**
		* Removes the item at front of the list
		*/
		void PopFront();
		/**
		* Check whether the list is empty.
		* @return True if the list is empty.
		*/
		bool IsEmpty() const;
		/**
		* Get the item at the front of the list.
		* @return The item at the front.
		*/
		T& Front();
		/**
		* Get the item at the back of the list.
		* @return The item at the back.
		*/
		T& Back();
		/**
		* Get the item at the front of the list.
		* @return The item at the front.
		*/
		const T& Front() const;
		/**
		* Get the item at the back of the list.
		* @return The item at the back.
		*/
		const T& Back() const;
		/**
		* Get the current size of the list.
		* @return The number of items in the list (an integer).
		*/
		int32_t Size() const;
		/**
		* Deallocates all the dynamically allocated list items and initializes list's member variables.
		*/
		void Clear();
		/**
		* Assignment operator overloaded to perform a deep copy of list rhs into this list.
		* @param rhs The other list which has to be copied.
		* @return A deep copy of list rhs.
		*/
		SList& operator=(const SList &rhs);

		
		// Embedded iterator class
		// 
		// Will have a pointer to a node.
		// Overload == to see if two iterators point at the same node.
		// Also implement != for above.
		// Overload ++ to reassign the iterator to the next node.
		// Must implement both postfix and prefix with same result.
		// Dereference operator * to return the item contained by the node the iterator points to (T&). (Also have a const version)
		// 
		// Modifications in SList
		//
		// Begin, returns an iterator which points to the head of the list.
		// End, returns an iterator which points past the end of list (THINK).
		// InsertAfter, append the given item after the item the given iterator points to.
		// Find(const T & ) const, returns an iterator pointing to a given item.
		// Remove, shall remove the item associated with the given data maintain list integrity (Calling it on non-existing item shouldn't cause harm).
		//
		// Doxygen formatting, const correctness, unit testing, builds for all platforms and configurations.
		//
		// In Class Discussion
		//
		// A pointer to a node of the list.
		// A pointer to the owning list. (A const pointer)
		// A copy constructor
		// A assignment operator
		// 

		/**
		* An Iterator for the SList class, each object is associated with a specific node in a specific list.
		*/
		class Iterator
		{
		public:
			/**
			* Default constructor - Initializes an iterator with no owning list or pointed node.
			*/
			Iterator();
			/**
			* Copy constructor - Performs a deep copy of the passed iterator object into this iterator object.
			* @param It The iterator to copy.
			*/
			Iterator(const Iterator& It);
			// TODO Find a better way to do this
			Iterator(const Node* node, const SList* list);
			/**
			* Assignment operator overloaded to perform a deep copy of an iterator into this iterator.
			* @param It The iterator which has to be copied.
			* @return A deep copy of iterator It.
			*/
			Iterator& operator=(const Iterator& It);
			/**
			* Compares if two iterators point to the same node.
			* @return True if two iterators point to the same node.
			*/
			bool operator==(const Iterator & It) const;
			/**
			* Compares if two iterators don't point to the same node.
			* @return True if two iterators don't point to the same node.
			*/
			bool operator!=(const Iterator & It) const;
			/**
			* Overloaded pre-increment operator increments the node to which it points in the list.
			* @return Iterator pointing to the next node.
			*/
			Iterator& operator++();
			/**
			* Overloaded post-increment operator increments the node to which it points in the list.
			* @return Iterator pointing to the same node as before incrementing.
			*/			
			Iterator& operator++(int32_t postfix);
			/**
			* Dereference the item value the iterator points to.
			* @return Item in the list referred to by the iterator(T&).
			*/
			T& operator*();
			/**
			* Dereference the item value the iterator points to.
			* @return Item in the list referred to by the iterator(T&).
			*/
			const T& operator*() const;

		private:
			Node* m_pListNode;
			const SList* m_pOwnerList;

		};

		typename SList::Iterator& Begin() const;
		typename SList::Iterator& End() const;
		void InsertAfter(const T& listItem, const typename SList::Iterator& It);
		typename SList::Iterator& Find(const T& listItem) const;
		void Remove(T& listItem);
	};

}

#include "SList.inl"