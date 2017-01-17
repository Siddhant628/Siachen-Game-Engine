#include"pch.h"
#include "_SList.h"
#include <stdexcept>

namespace SiachenGameEngine
{
	_SList::_SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{

	}

	void _SList::PushFront(int32_t value)
	{
		Node* newNode = new Node();
		newNode->value = value;

		if (m_iSize == 0)
		{
			m_pBack = newNode;
		}
		newNode->nextNode = m_pFront;

		m_pFront = newNode;
		m_iSize++;
	}

	void _SList::PushBack(int32_t value)
	{
		Node* newNode = new Node();
		newNode->value = value;
		newNode->nextNode = nullptr;
		if (m_iSize == 0)
		{
			m_pFront = newNode;
		}
		m_pBack->nextNode = newNode;
		
		m_pBack = newNode;
		m_iSize++;
	}

	void _SList::PopFront()
	{
		Node* frontNode = m_pFront;

		m_pFront = m_pFront->nextNode;
		delete frontNode;
	}

	bool _SList::IsEmpty() const
	{
		return (m_iSize == 0);
	}

	int32_t _SList::Front() const
	{
		if (m_pFront == nullptr)
		{
			throw std::exception("The list is empty, front is null pointer.\n");
		}
		return m_pFront->value;
	}

	int32_t _SList::Back() const
	{
		if (m_pFront == nullptr)
		{
			throw std::exception("The list is empty, back is null pointer.\n");
		}
		return m_pBack->value;
	}

	int32_t _SList::Size() const
	{
		return m_iSize;
	}

	void _SList::Clear()
	{
		if (m_iSize == 0)
		{
			return;
		}
		Node* nextNode = m_pFront;
		if(m_iSize > 1)
		{
			do
			{
				nextNode = m_pFront->nextNode;
				delete m_pFront;
			} while (nextNode != m_pBack);
		}
		delete nextNode;
		m_pFront = nullptr;
		m_pBack = nullptr;
	}

}