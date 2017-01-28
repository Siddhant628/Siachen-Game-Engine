#include "Vector.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		// Vector Constructors

		template <typename T>
		Vector<T>::Vector() : mFront(nullptr), mSize(0), mCapacity(0)
		{

		}

		template<typename T>
		Vector<T>::Vector(const Vector& rhs) : mCapacity(rhs.mCapacity), mSize(rhs.mSize)
		{
			mFront = static_cast<T*>(malloc(mCapacity * sizeof(T)));
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				new (mFront + index)T(rhs.mFront[index]);
			}
		}

		template <typename T>
		Vector<T>::~Vector()
		{
			ClearAndFree();
		}

		// Vector Methods

		template<typename T>
		bool Vector<T>::IsEmpty() const
		{
			return (mSize == 0);
		}

		template<typename T>
		T& Vector<T>::Front()
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The vector is empty.\n");
			}
			return *mFront;
		}

		template<typename T>
		const T& Vector<T>::Front() const
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The vector is empty.\n");
			}
			return *mFront;
		}

		template<typename T>
		T& Vector<T>::Back()
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The vector is empty.\n");
			}
			return mFront[mSize - 1];
		}

		template<typename T>
		const T& Vector<T>::Back() const
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The vector is empty.\n");
			}
			return mFront[mSize - 1];
		}

		template<typename T>
		std::uint32_t Vector<T>::Size() const
		{
			return mSize;
		}

		template<typename T>
		std::uint32_t Vector<T>::Capacity() const
		{
			return mCapacity;
		}

		template <typename T>
		typename Vector<T>::Iterator Vector<T>::PushBack(const T& data)
		{
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			new (mFront + mSize)T(data);
			++mSize;
			return Iterator(mSize-1, this);
		}

		template<typename T>
		void Vector<T>::PopBack()
		{
			if (IsEmpty())
			{
				return;
			}
			else
			{
				mFront[--mSize].~T();
			}
		}

		template<typename T>
		T& Vector<T>::At(std::uint32_t index) const
		{
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index, cannot access item beyond the vector.");
			}
			return mFront[index];
		}

		template<typename T>
		void Vector<T>::Reserve(std::uint32_t newCapacity)
		{
			if (newCapacity < mSize)
			{
				throw std::runtime_error("Reducing the size of memory would lead to loss of data.\n");
			}
			// In case this is the first allocated
			if (newCapacity == 0)
			{
				++newCapacity;
			}
			// Allocate the memory
			T* newBuffer = (T*)malloc(newCapacity*sizeof(T));
			// In case memory was allocated before
			if (mSize > 0)
			{
				memcpy(newBuffer, mFront, sizeof(T)*mSize);		// Move the data to new memory
				free(mFront);									// Deallocate old memory
			}
			// Update vector fields
			mFront = newBuffer;
			mCapacity = newCapacity;

		}

		template<typename T>
		void Vector<T>::Clear()
		{
			while (mSize > 0)
			{
				PopBack();
			}
		}

		template<typename T>
		void Vector<T>::ClearAndFree()
		{
			Clear();
			if (mFront == nullptr)
			{
				return;
			}
			free(mFront);
			mFront = nullptr;
			mCapacity = 0;
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::begin() const
		{
			return  Vector<T>::Iterator(0, this);
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::end() const
		{
			return  Vector<T>::Iterator(mSize, this);
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::Find(const T& data) const
		{
			for (Vector<T>::Iterator it = begin(); it != end(); ++it)
			{
				if (*it == data)
				{
					return it;
				}
			}
			return Vector<T>::Iterator(mSize, this);;
		}

		template<typename T>
		bool Vector<T>::Remove(const T& data)
		{
			for (Vector<T>::Iterator it = begin(); it != end(); ++it)
			{
				if (*it == data)
				{
					Vector<T>::Iterator it2 = it;
					return Remove(it, ++it2);
				}
			}
			return false;
		}

		template<typename T>
		bool Vector<T>::Remove(Iterator& beginIt, Iterator& endIt)
		{
			if ((beginIt.mOwnerVector != endIt.mOwnerVector) || (beginIt.mOwnerVector != this))
			{
				throw std::runtime_error("Invalid iterators for removing from the list.");
			}
			if ((beginIt.mIndexOffset > mSize) || (endIt.mIndexOffset > mSize) || (beginIt.mIndexOffset >= endIt.mIndexOffset))
			{
				throw std::out_of_range("Invalid iterator's for deletion.");
			}

			std::uint32_t beginIndex = beginIt.mIndexOffset;
			std::uint32_t endIndex = endIt.mIndexOffset;

			for (Vector<T>::Iterator it = beginIt; it != endIt; ++it)
			{
				(*it).~T();
			}

			T* destination = mFront + beginIndex;
			T* source = mFront + endIndex;
			memcpy(destination, source, sizeof(T)*(mSize - endIndex));
			mSize = mSize - (endIndex - beginIndex);

			return true;
		}

		// Vector Operators

		template<typename T>
		Vector<T>& Vector<T>::operator=(const Vector& rhs)
		{
			if (this != &rhs)
			{
				ClearAndFree();
				mFront = static_cast<T*>(malloc(rhs.mCapacity * sizeof(T)));
				for (std::uint32_t index = 0; index < rhs.mSize; ++index)
				{
					new (mFront + index)T(rhs.mFront[index]);
				}
				mCapacity = rhs.mCapacity;
				mSize = rhs.mSize;
			}
			return *this;
		}

		template<typename T>
		T& Vector<T>::operator[](std::uint32_t index)
		{
			if (index >= mSize)
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		template<typename T>
		const T& Vector<T>::operator[](std::uint32_t index) const
		{
			if (index >= mSize)
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		// Iterator Constructors

		template<typename T>
		Vector<T>::Iterator::Iterator() : mIndexOffset(0), mOwnerVector(nullptr)
		{

		}

		template<typename T>
		Vector<T>::Iterator::Iterator(const Iterator& rhs) : mIndexOffset(rhs.mIndexOffset), mOwnerVector(rhs.mOwnerVector)
		{

		}

		template<typename T>
		Vector<T>::Iterator::Iterator(const std::uint32_t offset,const Vector* ownerVector) : mIndexOffset(offset), mOwnerVector(ownerVector)
		{

		}
	
		// Iterator Operators

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
		{
			if (this != &rhs)
			{
				mIndexOffset = rhs.mIndexOffset;
				mOwnerVector = rhs.mOwnerVector;
			}
			return *this;
		}

		template<typename T>
		bool Vector<T>::Iterator::operator==(const Iterator& it) const
		{
			return ((mOwnerVector == it.mOwnerVector) && (mIndexOffset == it.mIndexOffset));
		}

		template<typename T>
		bool Vector<T>::Iterator::operator!=(const Iterator& it) const
		{
			return ((mOwnerVector != it.mOwnerVector) || (mIndexOffset != it.mIndexOffset));
		}

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
		{
			if (mOwnerVector == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, doesn't belong to any vector.");
			}
			// Including the case where the iterator points beyond the vector
			if (mIndexOffset >= mOwnerVector->mSize)
			{
				throw std::runtime_error("Incrementing the iterator out of the bounds.");
			}
			++mIndexOffset;
			return *this;
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::Iterator::operator++(std::int32_t)
		{
			if (mOwnerVector == nullptr)
			{
				throw std::runtime_error("Iterator cannot post-increment, doesn't belong to any vector.");
			}
			// Including the case where the iterator points beyond the vector
			if (mIndexOffset >= mOwnerVector->mSize)
			{
				throw std::runtime_error("Incrementing the iterator out of the bounds.");
			}
			Iterator tempIt = *this;
			++mIndexOffset;
			return tempIt;
		}

		template<typename T>
		T& Vector<T>::Iterator::operator*()
		{
			if (mOwnerVector == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a vector.");
			}
			if (mIndexOffset >= mOwnerVector->mSize)
			{
				throw std::out_of_range("Cannot dereference an items outside the vector.");
			}
			return mOwnerVector->mFront[mIndexOffset];
		}

		template<typename T>
		const T& Vector<T>::Iterator::operator*() const
		{
			if (mOwnerVector == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a vector.");
			}
			if (mIndexOffset >= mOwnerVector->mSize)
			{
				throw std::out_of_range("Cannot dereference an items outside the vector.");
			}
			return mOwnerVector->mFront[mIndexOffset];
		}
	}
}