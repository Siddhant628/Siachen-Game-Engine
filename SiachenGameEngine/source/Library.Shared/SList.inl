#include "SList.h"

namespace SiachenGameEngine
{
	template<typename T>
	SList<T>::SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{

	}

	template<typename T>
	SList<T>::SList(const SList &list) : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
	{
		Node* listFront = list.m_pFront;
		while (listFront != nullptr)
		{
			PushBack(listFront->value);
			listFront = listFront->nextNode;
		}
	}

	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	void SList<T>::PushFront(const T &value)
	{
		// Create a new node and set its value
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

		m_iSize++;
	}

	template<typename T>
	void SList<T>::PushBack(const T &value)
	{
		// Create a new node and set its value
		Node* newNode = new Node();
		newNode->value = value;
		newNode->nextNode = nullptr;
		// If it's the first node, it is the front item as well
		if (m_iSize == 0)
		{
			m_pFront = newNode;
		}
		else
		{
			m_pBack->nextNode = newNode;
		}
		m_pBack = newNode;

		m_iSize++;
	}

	template<typename T>
	void SList<T>::PopFront()
	{
		if (IsEmpty())
		{
			return;
		}
		Node* frontNode = m_pFront;
		if (m_iSize > 1)
		{
			m_pFront = m_pFront->nextNode;
		}
		else
		{
			m_pFront = nullptr;
			m_pBack = nullptr;
		}
		delete frontNode;
		m_iSize--;
	}

	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return (m_iSize == 0);
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::runtime_error("The list is empty, front is a null pointer.\n");
		}
		return m_pFront->value;
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::runtime_error("The list is empty, back is null pointer.\n");
		}
		return m_pBack->value;
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("The list is empty, front is a null pointer.\n");
		}
		return m_pFront->value;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("The list is empty, back is null pointer.\n");
		}
		return m_pBack->value;
	}

	template<typename T>
	int32_t SList<T>::Size() const
	{
		return m_iSize;
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while (m_iSize > 0)
		{
			PopFront();
		}
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Node* listFront = rhs.m_pFront;
			while (listFront != nullptr)
			{
				PushBack(listFront->value);
				listFront = listFront->nextNode;
			}
		}
		return *this;
	}
}