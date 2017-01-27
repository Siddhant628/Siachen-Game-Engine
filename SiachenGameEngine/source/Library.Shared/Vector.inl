#include "Vector.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		// Constructors

		template <typename T>
		Vector<T>::Vector() : mFront(nullptr), mSize(0), mCapacity(0)
		{

		}

		template<typename T>
		Vector<T>::Vector(const Vector& rhs) : mCapacity(rhs.mCapacity), mSize(rhs.mSize)
		{
			T* mFront = static_cast<T*>(malloc(mCapacity * sizeof(T)));
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

		// Methods

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
		void Vector<T>::PushBack(const T& data)
		{
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mFront[mSize] = data;
			++mSize;
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
			if (index > mSize - 1)
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
			if (mCapacity > 1)
			{
				memcpy(newBuffer, mFront, sizeof(T)*mSize);		// Move the data to new memory
				
				for (std::int32_t index = 0; index < mSize; ++index)
				{
					mFront[index].~T();
				}

				free(mFront);									// Deallocate old memory
			}
			// Update vector fields
			mFront = newBuffer;
			mCapacity = newCapacity;

		}

		template<typename T>
		void Vector<T>::Clear()
		{
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				mFront[index].~T();
			}
			mSize = 0;
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

		// Overloaded operators

		template<typename T>
		Vector<T>& Vector<T>::operator=(const Vector& rhs)
		{
			if (this != rhs)
			{
				ClearAndFree();
				T* mFront = static_cast<T*>(malloc(rhs.mCapacity * sizeof(T)));
				for (std::int32_t index = 0; index < mSize; ++index)
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
			if (index > (mSize - 1))
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		template<typename T>
		const T& Vector<T>::operator[](std::uint32_t index) const
		{
			if (index > (mSize - 1))
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		// Iterator

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
			if (mIndexOffset == mSize)
			{
				return *this;
			}
			++mIndexOffset;
			return *this;
		}

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator++(std::int32_t)
		{
			if (mOwnerVector == nullptr)
			{
				throw std::runtime_error("Iterator cannot post-increment, doesn't belong to any vector.");
			}
			// Including the case where the iterator points beyond the vector
			if (mIndexOffset == mSize)
			{
				return *this;
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
			if (mIndexOffset > (mOwnerVector->mSize - 1))
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
			if (mIndexOffset > (mOwnerVector->mSize - 1))
			{
				throw std::out_of_range("Cannot dereference an items outside the vector.");
			}
			return mOwnerVector->mFront[mIndexOffset];
		}
	}
}