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

	private:
		struct Node
		{
			Node* nextNode;
			T value;
		};

		Node* m_pFront;
		Node* m_pBack;

		int32_t m_iSize;
	};

}

#include "SList.inl"