// A templated class which implements a singly - linked list container.

#pragma once

namespace SiachenGameEngine
{
	namespace Containers
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

			Node* mFront;
			Node* mBack;

			int32_t mSize;

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

			/**
			* An Iterator for the SList class, each object is associated with a specific node in a specific list.
			*/
			class Iterator
			{
				friend class SList;

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
				Iterator operator++(int32_t postfix);
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
				Iterator(Node* node, const SList* list);

				Node* m_pListNode;
				const SList* m_pOwnerList;

			};

			/**
			* Inserts an item at the front of the list.
			* @param obj The item to insert at the front.
			* @see PushBack()
			*/
			typename SList::Iterator PushFront(const T& obj);
			/**
			* Inserts an item at the back of the list.
			* @param obj The item to insert at the back.
			* @see PushFront()
			*/
			typename SList::Iterator PushBack(const T& obj);
			/**
			* Returns an iterator which points to the item at the beginning of this list.
			* @return Iterator associated with the front node of this list.
			*/
			typename SList::Iterator begin() const;
			/**
			* Returns an iterator which points to the item at the end of this list.
			* @return Iterator associated with the back node of this list.
			*/
			typename SList::Iterator end() const;
			/**
			* Insert a node after a specific item in the list.
			* @param listItem The T type item which has to be inserted in the list.
			* @param It The iterator associated with the item in the list after which listItem has to be inserted.
			*/
			typename SList::Iterator InsertAfter(const T& listItem, const typename SList::Iterator& It);
			/**
			* Searches for an item in the list and provide an iterator associated with it.
			* @param listItem The item which has to be found in the list.
			* @return An iterator associated with a the item searched for in the list.
			*/
			typename SList::Iterator Find(const T& listItem) const;
			/**
			* Removes the argument item from the list, if it is present.
			* @param listItem The item in this list which has to be removed.
			* @return True if an item was removed.
			*/
			bool Remove(const T& listItem);
		};
	}
}

#include "SList.inl"