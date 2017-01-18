#pragma once
#include "pch.h"

namespace SiachenGameEngine
{
	template <class T>
	class SList
	{
	public:
		// Initializes an empty list
		SList();
		// Copy constructor (performs a deep copy)
		SList(const SList &list);
		
		~SList();
		
		// Insert given number into the list
		void PushFront(const T &);
		// Insert given number at the end of the list
		void PushBack(const T &);
		// Removes the first number of the list
		void PopFront();
		// Indicates whether a list contains any items
		bool IsEmpty() const;
		// Returns the first item in the list
		T& Front();
		// Returns the last item in the list
		T& Back();
		// Returns the first item in the list
		const T& Front() const;
		// Returns the last item in the list
		const T& Back() const;
		// Returns the number of items in the list
		int32_t Size() const;
		// Clears all items in the list
		void Clear();
		// TODO operator=

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