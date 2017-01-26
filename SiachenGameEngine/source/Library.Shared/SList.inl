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
			if (It.mOwnerList != this)
			{
				throw std::runtime_error("Cannot insert node in another list.");
			}
			// Create a new node
			Node* newNode = new Node();
			newNode->value = listItem;

			// Insert the node at the appropriate place
			if (It.mListNode == nullptr || It.mListNode->nextNode == nullptr)
			{
				mBack->nextNode = newNode;
				mBack = newNode;
			}
			else
			{
				Node* nodeToInsertBefore = It.mListNode->nextNode;
				newNode->nextNode = nodeToInsertBefore;
				It.mListNode->nextNode = newNode;
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
					if (It.mListNode->nextNode != nullptr && It.mListNode->nextNode->value == listItem)
					{
						Node* nodeBefore = It.mListNode;
						Node* nodeToRemove = It.mListNode->nextNode;
						
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
		SList <T>::Iterator::Iterator() : mListNode(nullptr), mOwnerList(nullptr)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(const Iterator& It) : mOwnerList(It.mOwnerList), mListNode(It.mListNode)
		{

		}

		template<typename T>
		SList<T>::Iterator::Iterator(Node* node, const SList* list) : mListNode(node), mOwnerList(list)
		{

		}

		// Overloaded operators for the Iterator
		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& It)
		{
			if (this != &It)
			{
				mListNode = It.mListNode;
				mOwnerList = It.mOwnerList;
			}
			return *this;
		}

		template<typename T>
		bool SList<T>::Iterator::operator==(const Iterator& It) const
		{
			return ((It.mOwnerList == mOwnerList) && (It.mListNode == mListNode));
		}

		template<typename T>
		bool SList<T>::Iterator::operator!=(const Iterator& It) const
		{
			return ((It.mOwnerList != mOwnerList) || (It.mListNode != mListNode));
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator++()
		{
			if (mListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, end has been reached.\n");
			}
			if(mListNode != nullptr)
			{
				mListNode = mListNode->nextNode;
			}
			return *this;
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::Iterator::operator++(int32_t)
		{
			if (mListNode == nullptr)
			{
				throw std::runtime_error("Iterator cannot post-increment, end has been reached.\n");
			}
			Iterator iteratorToReturn = *this;
			if (mListNode != nullptr)
			{
				mListNode = mListNode->nextNode;
			}
			return iteratorToReturn;
		}

		template<typename T>
		T& SList<T>::Iterator::operator*()
		{
			if (mListNode == nullptr)
			{
				throw std::runtime_error("Iterator points at the end of the list, cannot return an item.");
			}
			return mListNode->value;
		}

		template<typename T>
		const T& SList<T>::Iterator::operator*() const
		{
			if (mListNode == nullptr)
			{
				throw std::runtime_error("Iterator points at the end of the list, cannot return an item.");
			}
			return mListNode->value;
		}
	}
}