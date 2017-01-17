#include"pch.h"
#include "_SList.h"
#include <stdexcept>

namespace SiachenGameEngine
{

	_SList::_SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{

	}

	_SList::_SList(const _SList & _list)
	{
		Node* listFront = _list.m_pFront;
		while (listFront != nullptr)
		{
			// Copy value to new node
			Node* newNode = new Node();
			newNode->value = listFront->value;
			// If the list is empty, then the new node is back as well
			if (m_iSize == 0)
			{
				m_pBack = newNode;
				newNode->nextNode = nullptr;
			}
			else
			{
				newNode->nextNode = m_pFront;
			}
			// Update the front and the size
			m_pFront = newNode;
			m_iSize++;
			// Proceed to next item in the list
			listFront = listFront->nextNode;
		}
	}
	
	void _SList::PushFront(int32_t value)
	{
		// Create a new node and set it's value
		Node* newNode = new Node();
		newNode->value = value;
		// If it's the first node, it is the back item as well
		if (m_iSize == 0)
		{
			m_pBack = newNode;
			newNode->nextNode = nullptr;
		}
		else
		{
			newNode->nextNode = m_pFront;
		}
		// Set this node as the front
		m_pFront = newNode;
		// Increment the size of list
		m_iSize++;
	}

	void _SList::PushBack(int32_t value)
	{
		// Create a new node and set it's value
		Node* newNode = new Node();
		newNode->value = value;
		newNode->nextNode = nullptr;
		// // If it's the first node, it is the front item as well
		if (m_iSize == 0)
		{
			m_pFront = newNode;
		}
		else
		{
			m_pBack->nextNode = newNode;
		}
		m_pBack = newNode;
		// Increment the size of list
		m_iSize++;
	}

	int32_t _SList::PopFront()
	{
		if (m_pFront == nullptr)
		{
			throw std::runtime_error("The list is empty, front is a null pointer.\n");
		}
		// Store front node in temp variable
		Node* frontNode = m_pFront;
		int32_t value = frontNode->value;
		// Update front and delete node
		m_pFront = m_pFront->nextNode;
		delete frontNode;
		m_iSize--;

		return value;
	}

	bool _SList::IsEmpty() const
	{
		return (m_iSize == 0);
	}

	int32_t _SList::Front() const
	{
		if (m_pFront == nullptr)
		{
			throw std::runtime_error("The list is empty, front is a null pointer.\n");
		}
		return m_pFront->value;
	}

	int32_t _SList::Back() const
	{
		if (m_pBack == nullptr)
		{
			throw std::runtime_error("The list is empty, back is null pointer.\n");
		}
		return m_pBack->value;
	}

	int32_t _SList::Size() const
	{
		return m_iSize;
	}

	void _SList::Clear()
	{
		// If list is empty then return
		if (m_iSize == 0)
		{
			return;
		}
		// Loop through the nodes and delete them
		Node* nextNode = m_pFront;
		do
		{
			nextNode = m_pFront->nextNode;
			delete m_pFront;
			m_pFront = nextNode;
		} while (m_pFront != nullptr);
		// Update member variables
		m_pBack = nullptr;
		m_iSize = 0;
	}

	_SList::~_SList()
	{
		_SList::Clear();
	}
}