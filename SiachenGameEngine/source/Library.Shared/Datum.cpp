#include "Datum.h"
#define GLM_FORCE_CXX11
#include "../../external/glm/glm/glm.hpp"

namespace SiachenGameEngine
{
	namespace Containers
	{
		Datum::Datum() : mSize(0), mCapacity(0), mDatumType(DatumType::UnknownType), mIsExternal(false)
		{
			mData.vp = nullptr;
		}

		Datum::Datum(const Datum & rhs) : mDatumType(rhs.mDatumType), mSize(0), mCapacity(0), mIsExternal(false)
		{
			if		(mDatumType == DatumType::IntegerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.i[index]);
			else if (mDatumType == DatumType::FloatType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.f[index]);
			else if (mDatumType == DatumType::StringType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.s[index]);
			else if (mDatumType == DatumType::VectorType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.v[index]);
			else if (mDatumType == DatumType::MatrixType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.m[index]);
			else if (mDatumType == DatumType::PointerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.r[index]);
			// TODO Scope
		}

		Datum& Datum::operator=(const Datum & rhs)
		{
			if (this != &rhs)
			{
				// Clear the previously owned data
				if (!mIsExternal)
				{
					ClearAndFree();
				}
				// In case the data in external array
				else
				{
					mSize = 0;
					mCapacity = 0;
					mIsExternal = false;
					mData.vp = nullptr;
				}
				mDatumType = rhs.mDatumType;
				// Copy the data from rhs
				if		(mDatumType == DatumType::IntegerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.i[index]);
				else if (mDatumType == DatumType::FloatType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.f[index]);
				else if (mDatumType == DatumType::StringType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.s[index]);
				else if (mDatumType == DatumType::VectorType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.v[index]);
				else if (mDatumType == DatumType::MatrixType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.m[index]);
				else if (mDatumType == DatumType::PointerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.r[index]);
				// TODO Scope
			}
			return *this;
		}

		Datum::~Datum()
		{
			if(!mIsExternal) ClearAndFree();
		}

		DatumType Datum::Type() const
		{
			return mDatumType;
		}

		void Datum::SetType(DatumType setType)
		{
			if (mDatumType != DatumType::UnknownType)
			{
				throw std::runtime_error("This datum has already been assigned a type.");
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
			if (mIsExternal)
			{
				throw std::runtime_error("Cannot reserve memory for an external array.");
			}
			if ((newCapacity < mSize) || (mDatumType == DatumType::UnknownType))
			{
				throw std::runtime_error("Invalid reserve request.");
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::IntegerType);
			}
			if ((mDatumType != DatumType::IntegerType) || mIsExternal)
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::FloatType);
			}
			if ((mDatumType != DatumType::FloatType) || mIsExternal)
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::StringType);
			}
			if ((mDatumType != DatumType::StringType) || mIsExternal)
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::VectorType);
			}
			if ((mDatumType != DatumType::VectorType) || mIsExternal)
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::MatrixType);
			}
			if ((mDatumType != DatumType::MatrixType) || mIsExternal)
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
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::PointerType);
			}
			if ((mDatumType != DatumType::PointerType) || mIsExternal)
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			//mData.r[mSize] = const_cast<GameplayFramework::RTTI*>(data);
			new (mData.r + mSize)GameplayFramework::RTTI*(const_cast<GameplayFramework::RTTI*>(data));
			++mSize;
		}

		void Datum::PopBack()
		{
			if (mIsExternal || mDatumType == DatumType::UnknownType)
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
				else if (mDatumType == DatumType::PointerType)	--mSize;
				// TODO Scope
			}
		}

		void Datum::Clear()
		{
			if (mIsExternal)
			{
				throw std::runtime_error("Cannot clear external array.");
			}
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
			// TODO Cannot free string!
			free(mData.vp);
			
			mData.vp = nullptr;
			mCapacity = 0;
		}

		void Datum::Set(std::int32_t value, std::uint32_t index)
		{
			if (mDatumType != DatumType::IntegerType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.i[index].std::int32_t::~int32_t();
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
			if (mDatumType != DatumType::FloatType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.f[index].std::float_t::~float_t();
				new (mData.f + index)std::float_t(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(glm::vec4& value, std::uint32_t index)
		{
			if (mDatumType != DatumType::VectorType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.v[index].glm::vec4::~vec4();
				new (mData.v + index)glm::vec4(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(glm::mat4x4& value, std::uint32_t index)
		{
			if (mDatumType != DatumType::MatrixType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.m[index].glm::mat4x4::~mat4x4();
				new (mData.m + index)glm::mat4x4(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		void Datum::Set(std::string& value, std::uint32_t index)
		{
			if (mDatumType != DatumType::StringType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.s[index].std::string::~string();
				new (mData.s + index)std::string(value);
			}
			else if (mIsExternal)
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			PushBack(value);
		}

		// TODO CHECK Placement New
		void Datum::Set(GameplayFramework::RTTI* value, std::uint32_t index)
		{
			if (mDatumType != DatumType::PointerType)
			{
				throw std::runtime_error("Improper set operation.");
			}
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

		bool Datum::operator==(const Datum & rhs) const
		{
			if (mDatumType == DatumType::UnknownType || rhs.mDatumType == DatumType::UnknownType)
			{
				throw std::runtime_error("Cannot compare unknown types.");
			}
			if ((mSize != rhs.mSize) || (mDatumType != rhs.mDatumType))
			{
				return false;
			}
			// In case of a string
			if (mDatumType == DatumType::StringType)
			{
				for (std::uint32_t index = 0; index < mSize; ++index)
				{
					if (mData.s[index] != rhs.mData.s[index])	return false;
				}
				return true;
			}
			// In case of a RTTI* type
			else if (mDatumType == DatumType::PointerType)
			{
				for (std::uint32_t index = 0; index < mSize; ++index)
				{
					if (!(mData.r[index]->Equals(rhs.mData.r[index])))	return false;
				}
				return true;
			}
			// In case of any other type
			std::uint32_t sizeOfElement = 0;
			if		(mDatumType == DatumType::IntegerType)	sizeOfElement = sizeof(std::int32_t);
			else if (mDatumType == DatumType::FloatType)	sizeOfElement = sizeof(std::float_t);
			else if (mDatumType == DatumType::MatrixType)	sizeOfElement = sizeof(glm::mat4x4);
			else if (mDatumType == DatumType::VectorType)	sizeOfElement = sizeof(glm::vec4);
			
			return (std::memcmp(mData.vp, rhs.mData.vp, sizeOfElement*mSize) == 0);

			// TODO Scope
		}

		bool Datum::operator!=(const Datum & rhs) const
		{
			if (mDatumType == DatumType::UnknownType || rhs.mDatumType == DatumType::UnknownType)
			{
				throw std::runtime_error("Cannot compare unknown types.");
			}
			if ((mSize != rhs.mSize) || (mDatumType != rhs.mDatumType))
			{
				return true;
			}
			// In case of a string
			if (mDatumType == DatumType::StringType)
			{
				for (std::uint32_t index = 0; index < mSize; ++index)
				{
					if (mData.s[index] != rhs.mData.s[index])	return true;
				}
				return false;
			}
			// In case of a RTTI* type
			else if (mDatumType == DatumType::PointerType)
			{
				for (std::uint32_t index = 0; index < mSize; ++index)
				{
					if (!(mData.r[index]->Equals(rhs.mData.r[index])))	return true;
				}
				return false;
			}
			// In case of any other type
			std::uint32_t sizeOfElement = 0;
			if		(mDatumType == DatumType::IntegerType)	sizeOfElement = sizeof(std::int32_t);
			else if (mDatumType == DatumType::FloatType)	sizeOfElement = sizeof(std::float_t);
			else if (mDatumType == DatumType::MatrixType)	sizeOfElement = sizeof(glm::mat4x4);
			else if (mDatumType == DatumType::VectorType)	sizeOfElement = sizeof(glm::vec4);
			
			return (std::memcmp(mData.vp, rhs.mData.vp, sizeOfElement*mSize) != 0);

			// TODO Scope
		}

		bool Datum::operator==(const std::int32_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::IntegerType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.i[0] == rhs);
		}

		bool Datum::operator==(const std::float_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::FloatType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.f[0] == rhs);
		}

		bool Datum::operator==(const std::string& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::StringType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.s[0] == rhs);
		}

		bool Datum::operator==(const glm::vec4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::VectorType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.v[0] == rhs);
		}

		bool Datum::operator==(const glm::mat4x4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::MatrixType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.m[0] == rhs);
		}

		bool Datum::operator==(const GameplayFramework::RTTI* rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::PointerType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.r[0] == rhs);
		}

		bool Datum::operator!=(const std::int32_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::IntegerType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.i[0] != rhs);
		}

		bool Datum::operator!=(const std::float_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::FloatType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.f[0] != rhs);
		}

		bool Datum::operator!=(const std::string& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::StringType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.s[0] != rhs);
		}

		bool Datum::operator!=(const glm::vec4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::VectorType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.v[0] != rhs);
		}

		bool Datum::operator!=(const glm::mat4x4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::MatrixType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.m[0] != rhs);
		}

		bool Datum::operator!=(const GameplayFramework::RTTI* rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::PointerType))
			{
				throw std::runtime_error("Invalid comparison operation.");
			}
			return (mData.r[0] != rhs);
		}

		void Datum::SetStorage(std::int32_t* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::IntegerType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.i = externalArray;
		}

		void Datum::SetStorage(std::float_t* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::FloatType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.f = externalArray;
		}

		void Datum::SetStorage(std::string* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::StringType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.s = externalArray;
		}

		void Datum::SetStorage(glm::vec4* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::VectorType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.v = externalArray;
		}

		void Datum::SetStorage(glm::mat4x4* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::MatrixType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.m = externalArray;
		}

		void Datum::SetStorage(GameplayFramework::RTTI** externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::PointerType || mIsExternal)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.r = externalArray;
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