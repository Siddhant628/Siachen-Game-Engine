#include "SList.h"

template<class T>
SiachenGameEngine::SList<T>::SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
{

}

template<class T>
SiachenGameEngine::SList<T>::SList(const SList &list): m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
{
	Node* listFront = list.m_pFront;
	while (listFront != nullptr)
	{
		PushBack(listFront->value);
		listFront = listFront->nextNode;
	}
}

template<class T>
SiachenGameEngine::SList<T>::~SList()
{
	Clear();
}

template<class T>
void SiachenGameEngine::SList<T>::PushFront(const T &value)
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

template<class T>
void SiachenGameEngine::SList<T>::PushBack(const T &value)
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

template<class T>
void SiachenGameEngine::SList<T>::PopFront()
{
	if (IsEmpty())
	{
		return;
	}
	Node* frontNode = m_pFront;
	m_pFront = m_pFront->nextNode;
	delete frontNode;
	m_iSize--;
}

template<class T>
bool SiachenGameEngine::SList<T>::IsEmpty() const
{
	return (m_iSize == 0);
}

template<class T>
T& SiachenGameEngine::SList<T>::Front()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The list is empty, front is a null pointer.\n");
	}
	return m_pFront->value;
}

template<class T>
T& SiachenGameEngine::SList<T>::Back()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The list is empty, back is null pointer.\n");
	}
	return m_pBack->value;
}

template<class T>
const T& SiachenGameEngine::SList<T>::Front() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("The list is empty, front is a null pointer.\n");
	}
	return m_pFront->value;
}

template<class T>
const T& SiachenGameEngine::SList<T>::Back() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("The list is empty, back is null pointer.\n");
	}
	return m_pBack->value;
}

template<class T>
int32_t SiachenGameEngine::SList<T>::Size() const
{
	return m_iSize;
}

template<class T>
void SiachenGameEngine::SList<T>::Clear()
{
	while (m_iSize > 0)
	{
		PopFront();
	}

}