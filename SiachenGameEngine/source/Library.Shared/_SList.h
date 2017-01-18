#pragma once

namespace SiachenGameEngine
{
	class _SList
	{

	public:
		// Initializes an empty list
		_SList();
		// Copy constructor
		_SList(const _SList &_list);

		~_SList();
		// Insert given number into the list
		void PushFront(int32_t);
		// Insert given number at the end of the list
		void PushBack(int32_t);
		// Removes the first number of the list
		void PopFront();
		// Indicates whether a list contains any items
		bool IsEmpty() const;
		// Returns the first item in the list
		int32_t Front() const;
		// Returns the last item in the list
		int32_t Back() const;
		// Returns the number of items in the list
		int32_t Size() const;
		// Clears all items in the list
		void Clear();

		// TODO Destructor, operator=, copy constructor 

	private:
		struct Node
		{
			Node* nextNode;
			int32_t value;
		};

		Node* m_pFront;
		Node* m_pBack;

		int32_t m_iSize;
	};
}