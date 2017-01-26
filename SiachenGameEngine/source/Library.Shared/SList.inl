#include "SList.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		template<typename T>
		SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0)
		{

		}

		template<typename T>
		SList<T>::SList(const SList<T>& list) : mFront(nullptr), mBack(nullptr), mSize(0)
		{

			for (Iterator It = list.begin(); It != list.end(); ++It)
			{
				PushBack(*It);
			}
		}

		template<typename T>
		SList<T>::~SList()
		{
			Clear();
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::PushFront(const T& value)
		{
			// Create a new node and set its value
			Node* newNode = new Node();
			newNode->value = value;
			// If it's the first node, it is the back item as well
			if (mSize == 0)
			{
				mBack = newNode;
				newNode->nextNode = nullptr;
			}
			else
			{
				newNode->nextNode = mFront;
			}
			// Set this node as the front
			mFront = newNode;
			mSize++;
			return Iterator(mFront, this);
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::PushBack(const T& value)
		{
			// Create a new node and set its value
			Node* newNode = new Node();
			newNode->value = value;
			newNode->nextNode = nullptr;
			// If it's the first node, it is the front item as well
			if (mSize == 0)
			{
				mFront = newNode;
			}
			else
			{
				mBack->nextNode = newNode;
			}
			mBack = newNode;
			mSize++;
			return Iterator(mBack, this);
		}

		template<typename T>
		void SList<T>::PopFront()
		{
			if (IsEmpty())
			{
				return;
			}
			Node* frontNode = mFront;
			if (mSize > 1)
			{
				mFront = mFront->nextNode;
			}
			else
			{
				mFront = nullptr;
				mBack = nullptr;
			}
			delete frontNode;
			mSize--;
		}

		template<typename T>
		bool SList<T>::IsEmpty() const
		{
			return (mSize == 0);
		}

		template<typename T>
		T& SList<T>::Front()
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The list is empty, front is a null pointer.\n");
			}
			return mFront->value;
		}

		template<typename T>
		T& SList<T>::Back()
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The list is empty, back is null pointer.\n");
			}
			return mBack->value;
		}

		template<typename T>
		const T& SList<T>::Front() const
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The list is empty, front is a null pointer.\n");
			}
			return mFront->value;
		}

		template<typename T>
		const T& SList<T>::Back() const
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The list is empty, back is null pointer.\n");
			}
			return mBack->value;
		}

		template<typename T>
		int32_t SList<T>::Size() const
		{
			return mSize;
		}

		template<typename T>
		void SList<T>::Clear()
		{
			while (mSize > 0)
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
				for (Iterator It = rhs.begin(); It != rhs.end(); ++It)
				{
					PushBack(*It);
				}
			}
			return *this;
		}

		// Methods of the list associated with its Iterator
		template<typename T>
		typename SList<T>::Iterator SList<T>::begin() const
		{
			return Iterator(mFront, this);
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::end() const
		{
			return Iterator(nullptr, this);
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::InsertAfter(const T& listItem, typename const SList::Iterator& It)
		{
			if (It.m_pOwnerList != this)
			{
				throw std::runtime_error("Cannot insert node in another list.");
			}
			// Create a new node
			Node* newNode = new Node();
			newNode->value = listItem;

			// Insert the node at the appropriate place
			if (It.m_pListNode == nullptr || It.m_pListNode->nextNode == nullptr)
			{
				mBack->nextNode = newNode;
				mBack = newNode;
			}
			else
			{
				Node* nodeToInsertBefore = It.m_pListNode->nextNode;
				newNode->nextNode = nodeToInsertBefore;
				It.m_pListNode->nextNode = newNode;
			}
			
			++mSize;

			return Iterator(newNode, this);
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::Find(const T& listItem) const
		{
			for (SList<T>::Iterator It = begin(); It != end(); ++It)
			{
				if (*It == listItem)
				{
					return It;
				}
			}
			return Iterator(nullptr, this);
		}

		template<typename T>
		bool SList<T>::Remove(const T& listItem)
		{
			if (IsEmpty())
			{
				return false;
			}
			if (mFront->value == listItem)
			{
				PopFront();
				return true;
			}
			for (SList<T>::Iterator It = begin(); It != end(); ++It)
			{
					if (It.m_pListNode->nextNode != nullptr && It.m_pListNode->nextNode->value == listItem)
					{
						Node* nodeBefore = It.m_pListNode;
						Node* nodeToRemove = It.m_pListNode->nextNode;
						
						if (nodeBefore->nextNode->nextNode == nullptr)
						{
							mBack = nodeBefore;
							nodeBefore->nextNode = nullptr;
						}
						else
						{
							Node* nodeAfter = nodeBefore->nextNode->nextNode;
							nodeBefore->nextNode = nodeAfter;
						}
						
						delete nodeToRemove;
						--mSize;
						
						return true;
					}
			}
			return false;
		}

		// Constructors for Iterator
		template<typename T>
		SList <T>::Iterator::Iterator() : m_pListNode(nullptr), m_pOwnerList(nullptr)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(const Iterator& It) : m_pOwnerList(It.m_pOwnerList), m_pListNode(It.m_pListNode)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(Node* node, const SList* list) : m_pListNode(node), m_pOwnerList(list)
		{

		}

		// Overloaded operators for the Iterator
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
			return ((It.m_pOwnerList == m_pOwnerList) && (It.m_pListNode == m_pListNode));
		}

		template<typename T>
		bool SList<T>::Iterator::operator!=(const Iterator& It) const
		{
			return ((It.m_pOwnerList != m_pOwnerList) || (It.m_pListNode != m_pListNode));
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator++()
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, end has been reached.\n");
			}
			if(m_pListNode != nullptr)
			{
				m_pListNode = m_pListNode->nextNode;
			}
			return *this;
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::Iterator::operator++(int32_t)
		{
			if (m_pListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot post-increment, end has been reached.\n");
			}
			Iterator iteratorToReturn = *this;
			if (m_pListNode != nullptr)
			{
				m_pListNode = m_pListNode->nextNode;
			}
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