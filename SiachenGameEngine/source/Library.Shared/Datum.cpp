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
			// TODO Scope

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
			//mData.i[mSize] = data;
			new (mData.i + mSize)std::int32_t(data);
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
			//mData.f[mSize] = data;
			new (mData.f + mSize)std::float_t(data);
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
			//mData.s[mSize] = data;
			new (mData.s + mSize)std::string(data);
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
			//mData.v[mSize] = data;
			new (mData.v + mSize)glm::vec4(data);
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
			//mData.m[mSize] = data;
			new (mData.m + mSize)glm::mat4x4(data);
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
			//mData.r[mSize] = const_cast<GameplayFramework::RTTI*>(data);
			new (mData.f + mSize)GameplayFramework::RTTI*(const_cast<GameplayFramework::RTTI*>(data));
			++mSize;
		}

		void Datum::PopBack()
		{
			if (mIsExternal == true || mDatumType == DatumType::UnknownType)
			{
				throw std::runtime_error("Invalid pop operation.");
			}
			if (IsEmpty())
			{
				return;
			}
			else
			{
				if		(mDatumType == DatumType::IntegerType)	mData.i[--mSize].std::int32_t::~int32_t();
				else if (mDatumType == DatumType::FloatType)	mData.f[--mSize].std::float_t::~float_t();
				else if (mDatumType == DatumType::VectorType)	mData.v[--mSize].glm::vec4::~vec4();
				else if (mDatumType == DatumType::MatrixType)	mData.m[--mSize].glm::mat4x4::~mat4x4();
				else if (mDatumType == DatumType::StringType)	mData.s[--mSize].std::string::~string();
				//else if (mDatumType == DatumType::PointerType)	mData.r[--mSize].GameplayFramework::RTTI::~RTTI*();
				// TODO Scope
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

		void Datum::Set(std::int32_t value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.i + index)std::int32_t(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(std::float_t value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.f + index)std::float_t(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(glm::vec4 value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.f + index)glm::vec4(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(glm::mat4x4 value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.f + index)glm::mat4x4(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(std::string value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.f + index)std::string(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		// TODO CHECK Placement new
		void Datum::Set(GameplayFramework::RTTI* value, std::uint32_t index)
		{
			if (mSize > index)
			{
				new (mData.f + index)GameplayFramework::RTTI*(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
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