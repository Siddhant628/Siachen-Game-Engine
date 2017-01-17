#include"pch.h"
#include "_SList.h"
#include <stdexcept>

namespace SiachenGameEngine
{

	_SList::_SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{

	}

	_SList::_SList(const _SList & _list) : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{
		Node* listFront = _list.m_pFront;
		while (listFront != nullptr)
		{
			PushBack(listFront->value);
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

	void _SList::PopFront()
	{
		// Return if the list is already empty
		if (IsEmpty())
		{
			return;
		}
		Node* frontNode = m_pFront;
		m_pFront = m_pFront->nextNode;
		delete frontNode;
		m_iSize--;
	}

	bool _SList::IsEmpty() const
	{
		return (m_iSize == 0);
	}

	int32_t _SList::Front() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("The list is empty, front is a null pointer.\n");
		}
		return m_pFront->value;
	}

	int32_t _SList::Back() const
	{
		if (IsEmpty())
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
		if (IsEmpty())
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