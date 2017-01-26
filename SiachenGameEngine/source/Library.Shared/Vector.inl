#include "Vector.h"
#

namespace SiachenGameEngine
{
	namespace Containers
	{
		template <typename T>
		Vector<T>::Vector() : mFront(nullptr), mSize(0), mCapacity(0)
		{

		}

		template<typename T>
		T& Vector<T>::operator[](uint32_t index)
		{
			if (index > mSize)
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		template<typename T>
		const T& Vector<T>::operator[](uint32_t index) const
		{
			if (index > mSize)
			{
				throw std::out_of_range("The index is invalid for this vector.\n");
			}
			return *(mFront + index);
		}

		template<typename T>
		bool Vector<T>::IsEmpty()
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
			return *(mFront + mSize - 1);
		}

		template<typename T>
		const T& Vector<T>::Back() const
		{
			if (IsEmpty())
			{
				throw std::runtime_error("The vector is empty.\n");
			}
			return *(mFront + mSize - 1);
		}

		template<typename T>
		uint32_t Vector<T>::Size() const
		{
			return mSize;
		}

		template<typename T>
		uint32_t Vector<T>::Capacity() const
		{
			return mCapacity;
		}

		template <typename T>
		void Vector<T>::PushBack(const T& data)
		{
			// In case the vector is full
			if (mSize == mCapacity)
			{
				Reserve(mCapacity + 2);
			}
			++mSize;
			*(mFront + mSize) = data;
		}

		template<typename T>
		void Vector<T>::Reserve(uint32_t newCapacity)
		{
			if (newCapacity < mSize)
			{
				throw std::runtime_error("Reducing the size of memory would lead to loss of data.\n");
			}
			// Allocate the memory
			T* newBuffer = (T*)malloc(newCapacity*sizeof(T));
			// In case memory was allocated before
			if (mCapacity > 0)
			{
				memcpy(newBuffer, mFront, sizeof(T)*mSize);		// Copy the data
				
				for (int32_t it = 0; it < mSize; it++)
				{
					mFront[it].~T();
				}

				free(mFront);									// Deallocate obsolete memory
			}
			// Update vector fields
			mFront = newBuffer;
			mCapacity = newCapacity;

		}

		template<typename T>
		void Vector<T>::Clear()
		{
			for (int32_t it = 0; it < mSize; it++)
			{
				mFront[it].~T();
			}
			free(mFront);
			mFront = nullptr;
			mSize = 0;
			mCapacity = 0;
		}
	
	}
}