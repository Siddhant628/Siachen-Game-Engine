#include "SList.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		template<typename T>
		SList<T>::SList() : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
		{

		}

		template<typename T>
		SList<T>::SList(const SList<T>& list) : m_pFront(nullptr), m_pBack(nullptr), m_iSize(0)
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
		void SList<T>::PushFront(const T& value)
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
		void SList<T>::PushBack(const T& value)
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
		SList<T>& SList<T>::operator=(const SList<T>& rhs)
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

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Begin() const
		{
			return Iterator(m_pFront, this);
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::End() const
		{
			return Iterator(m_pBack, this);
		}

		template<typename T>
		void SList<T>::InsertAfter(const T& listItem, typename const SList::Iterator& It)
		{
			// Create a new node
			Node* newNode = new Node();
			newNode->value = listItem;
			// Insert the node at the appropriate place
			Node* nodeToInsertBefore = It.m_pListNode->nextNode;
			It.m_pListNode->nextNode = newNode;
			newNode->nextNode = nodeToInsertBefore;
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Find(const T& listItem) const
		{
			for (SList<T>::Iterator It = Begin(); It != End(); ++It)
			{
				if (It.m_pListNode->value == listItem)
				{
					return It;
				}
			}
			return Iterator(nullptr, this);
		}

		template<typename T>
		bool SList<T>::Remove(const T& listItem)
		{
			for (SList<T>::Iterator It = Begin(); It != End(); ++It)
			{
				if (It.m_pListNode->nextNode->value == listItem)
				{
					Node* nodeBefore = It.m_pListNode;
					Node* nodeAfter = nodeBefore->nextNode->nextNode;
					delete nodeBefore->nextNode;
					nodeBefore->nextNode = nodeAfter;
					return true;
				}
			}
			return false;
		}

		template<typename T>
		SList <T>::Iterator::Iterator() : m_pListNode(nullptr), m_pOwnerList(nullptr)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(const Iterator& It) : m_pOwnerList(It.m_pOwnerList), m_pListNode(It.m_pListNode)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(const Node * node, const SList * list) : m_pListNode(node), m_pOwnerList(list)
		{

		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& It)
		{
			if (this != &It)
			{
				m_pListNode = It.m_pListNode;
				m_pOwnerList = It.m_pOwnerList;
			}
			return *this;
		}

		template<typename T>
		bool SList<T>::Iterator::operator==(const Iterator& It) const
		{
			return (It.m_pListNode == m_pListNode);
		}

		template<typename T>
		bool SList<T>::Iterator::operator!=(const Iterator& It) const
		{
			return (It.m_pListNode != m_pListNode);
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator++()
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, end has been reached.\n");
			}
			m_pListNode = m_pListNode->nextNode;
			return *this;
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator++(int32_t postfix)
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot post-increment, end has been reached.\n");
			}
			Iterator iteratorToReturn = *this;
			m_pListNode = m_pListNode->nextNode;
			return iteratorToReturn;
		}

		template<typename T>
		T& SList<T>::Iterator::operator*()
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator points at the end of the list, cannot return an item.");
			}
			return m_pListNode->value;
		}

		template<typename T>
		const T& SList<T>::Iterator::operator*() const
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator points at the end of the list, cannot return an item.");
			}
			return m_pListNode->value;
		}
	}
}