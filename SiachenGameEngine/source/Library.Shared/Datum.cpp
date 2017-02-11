#include "Datum.h"


namespace SiachenGameEngine
{
	namespace Containers
	{
		Datum::Datum() : mSize(0), mCapacity(0), mDatumType(DatumType::UnknownType), mIsExternal(false)
		{
			mData.vp = nullptr;
		}

		Datum::~Datum()
		{
			ClearAndFree();
		}

		DatumType Datum::Type() const
		{
			return mDatumType;
		}

		void Datum::SetType(DatumType setType)
		{
			if (mDatumType != DatumType::UnknownType)
			{
				throw std::runtime_error("This datum has already been assigned a type");
			}
			mDatumType = setType;
		}

		std::uint32_t Datum::Size() const
		{
			return mSize;
		}

		bool Datum::IsEmpty()
		{
			return (mSize == 0);
		}

		void Datum::Reserve(std::uint32_t newCapacity)
		{
			if (newCapacity < mSize)
			{
				throw std::runtime_error("Capacity cannot be less than the current size.");
			}
			if (mDatumType == DatumType::UnknownType)
			{
				throw std::runtime_error("Cannot reserve memory for an unknown type");
			}
			// In case no memory is allocated and the capacity is 0.
			if (newCapacity == 0)
			{
				++newCapacity;
			}
			// Estimate the size of data items
			std::uint32_t sizeOfData;
			if		(mDatumType == DatumType::IntegerType)		sizeOfData = sizeof(std::int32_t);
			else if (mDatumType == DatumType::FloatType)		sizeOfData = sizeof(std::float_t);
			else if (mDatumType == DatumType::VectorType)		sizeOfData = sizeof(glm::vec4);
			else if (mDatumType == DatumType::MatrixType)		sizeOfData = sizeof(glm::mat4x4);
			else if (mDatumType == DatumType::StringType)		sizeOfData = sizeof(std::string);
			else if (mDatumType == DatumType::PointerType)		sizeOfData = sizeof(GameplayFramework::RTTI*);
			// TODO Add condition for a Scope class

			// Allocate the memory
			void* newBuffer = malloc(newCapacity * sizeof(sizeOfData));
			if (mSize > 0)
			{
				memcpy(newBuffer, mData.vp, sizeof(sizeOfData)*mSize);
				free(mData.vp);
			}
			mData.vp = newBuffer;
			mCapacity = newCapacity;
		}

		void Datum::PushBack(const std::int32_t data)
		{
			if ((mDatumType != DatumType::IntegerType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.i[mSize] = data;
			++mSize;
		}

		void Datum::PushBack(const std::float_t data)
		{
			if ((mDatumType != DatumType::FloatType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.f[mSize] = data;
			++mSize;
		}

		void Datum::PushBack(const std::string& data)
		{
			if ((mDatumType != DatumType::StringType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.s[mSize] = data;
			++mSize;
		}

		void Datum::PushBack(const glm::vec4& data)
		{
			if ((mDatumType != DatumType::VectorType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.v[mSize] = data;
			++mSize;
		}

		void Datum::PushBack(const glm::mat4x4& data)
		{
			if ((mDatumType != DatumType::MatrixType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.m[mSize] = data;
			++mSize;
		}

		void Datum::PushBack(const GameplayFramework::RTTI* data)
		{
			if ((mDatumType != DatumType::PointerType) || (mIsExternal == true))
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.r[mSize] = const_cast<GameplayFramework::RTTI*>(data);
			++mSize;
		}

		void Datum::PopBack()
		{
			if (mIsExternal == true)
			{
				throw std::runtime_error("Invalid pop operation.");
			}
			if (IsEmpty())
			{
				return;
			}
			else
			{
				--mSize;
			}
		}

		void Datum::Clear()
		{
			while (mSize > 0)
			{
				PopBack();
			}
		}

		void Datum::ClearAndFree()
		{
			Clear();
			if (mData.vp == nullptr)
			{
				return;
			}
			free(mData.vp);
			mData.vp = nullptr;
			mCapacity = 0;
		}



		//Datum::Datum(const Datum& rhs)
		//{
		//	UNREFERENCED_PARAMETER(rhs);
		//}

		//Datum& Datum::operator=(const Datum& rhs)
		//{
		//	UNREFERENCED_PARAMETER(rhs);
		//	return *this;
		//}

		//Datum& Datum::operator=(const std::int32_t& rhs)
		//{
		//	UNREFERENCED_PARAMETER(rhs);
		//	DatumType thisType = this->mDatumType;
		//	if((thisType != DatumType::UnknownType) && (thisType != DatumType::IntegerType))
		//	{
		//		throw std::runtime_error("Cannot assign value to a datum of another type.");
		//	}
		//	return *this;
		//}
	}
}