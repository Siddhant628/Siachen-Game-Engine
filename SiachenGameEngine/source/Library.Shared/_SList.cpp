#include "_SList.h"

namespace SiachenGameEngine
{
	_SList::_SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{

	}

	void _SList::PushFront(int32_t value)
	{
		Node* newNode = new Node();
		
		if (m_iSize == 0)
		{
			m_pBack = newNode;
		}
		newNode->nextNode = m_pFront;
		newNode->value = value;

		m_pFront = newNode;
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
		return m_pFront->value;
	}

	int32_t _SList::Back() const
	{
		return m_pBack->value;
	}

	int32_t _SList::Size() const
	{
		return m_iSize;
	}

	void _SList::Clear()
	{
		Node* nextNode;
		if (m_iSize == 0)
		{
			return;
		}
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