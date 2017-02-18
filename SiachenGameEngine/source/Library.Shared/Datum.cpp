#include "pch.h"
#include "Datum.h"

#define GLM_FORCE_CXX98
#include <glm/gtx/string_cast.hpp>

namespace SiachenGameEngine
{
	namespace Containers
	{

		Datum::Datum() : mSize(0), mCapacity(0), mDatumType(DatumType::UnknownType), mIsExternal(false)
		{
			mData.vp = nullptr;
		}

		Datum::Datum(const Datum& rhs) : mDatumType(rhs.mDatumType), mSize(0), mCapacity(0), mIsExternal(false)
		{
			// If rhs is an external datum
			if (rhs.mIsExternal)
			{
				mIsExternal = true;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mData = rhs.mData;
			}
			// If rhs is an internal datum
			else
			{
				Reserve(10U);
				if		(mDatumType == DatumType::IntegerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.i[index]);
				else if (mDatumType == DatumType::FloatType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.f[index]);
				else if (mDatumType == DatumType::StringType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.s[index]);
				else if (mDatumType == DatumType::VectorType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.v[index]);
				else if (mDatumType == DatumType::MatrixType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.m[index]);
				else if (mDatumType == DatumType::PointerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.r[index]);
				else if (mDatumType == DatumType::TableType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.sc[index]);
			}
		}

		Datum& Datum::operator=(const Datum& rhs)
		{
			if (this != &rhs)
			{
				// Clear lhs datum if it is internal
				if (!mIsExternal)
				{
					ClearAndFree();
				}
				mDatumType = rhs.mDatumType;
				// If rhs datum is external, perform a shallow copy
				if (rhs.mIsExternal)
				{
					mIsExternal = true;
					mSize = rhs.mSize;
					mCapacity = rhs.mCapacity;
					mData = rhs.mData;
				}
				// If rhs datum is external, perform a deep copy
				else
				{
					mIsExternal = false;
					mSize = 0;
					mCapacity = 0;
					mData.vp = nullptr;
					Reserve(10U);
					if		(mDatumType == DatumType::IntegerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.i[index]);
					else if (mDatumType == DatumType::FloatType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.f[index]);
					else if (mDatumType == DatumType::StringType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.s[index]);
					else if (mDatumType == DatumType::VectorType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.v[index]);
					else if (mDatumType == DatumType::MatrixType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.m[index]);
					else if (mDatumType == DatumType::PointerType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.r[index]);
					else if (mDatumType == DatumType::TableType)	for (std::uint32_t index = 0; index < rhs.mSize; ++index)		PushBack(rhs.mData.sc[index]);
				}
			}
			return *this;
		}

		Datum::~Datum()
		{
			if (!mIsExternal) ClearAndFree();
		}


		DatumType Datum::Type() const
		{
			return mDatumType;
		}

		void Datum::SetType(DatumType setType)
		{
			if (mDatumType == DatumType::UnknownType || setType == mDatumType)
			{
				mDatumType = setType;
			}
			else
			{
				throw std::runtime_error("This datum has already been assigned a type.");
			}
		}

		std::uint32_t Datum::Size() const
		{
			return mSize;
		}

		bool Datum::IsEmpty() const
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
			std::uint32_t sizeOfData = 0;
			if		(mDatumType == DatumType::IntegerType)		sizeOfData = sizeof(std::int32_t);
			else if (mDatumType == DatumType::FloatType)		sizeOfData = sizeof(std::float_t);
			else if (mDatumType == DatumType::VectorType)		sizeOfData = sizeof(glm::vec4);
			else if (mDatumType == DatumType::MatrixType)		sizeOfData = sizeof(glm::mat4x4);
			else if (mDatumType == DatumType::StringType)		sizeOfData = sizeof(std::string);
			else if (mDatumType == DatumType::PointerType)		sizeOfData = sizeof(GameplayFramework::RTTI*);
			else if (mDatumType == DatumType::TableType)		sizeOfData = sizeof(GameplayFramework::Scope*);


			// Allocate the memory
			void* newBuffer = malloc(newCapacity * sizeOfData);
			if (mSize > 0)
			{
				memcpy(newBuffer, mData.vp, sizeOfData*mSize);
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
			mData.r[mSize] = const_cast<GameplayFramework::RTTI*>(data);
			++mSize;
		}

		void Datum::PushBack(const GameplayFramework::Scope* data)
		{
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				SetType(DatumType::TableType);
			}
			if ((mDatumType != DatumType::TableType) || mIsExternal)
			{
				throw std::runtime_error("Invalid push operation.");
			}
			if (mSize == mCapacity)
			{
				Reserve(mCapacity * 2);
			}
			mData.sc[mSize] = const_cast<GameplayFramework::Scope*>(data);
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
				else
				{
					--mSize;
				}
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
			free(mData.vp);

			mData.vp = nullptr;
			mCapacity = 0;
		}

		void Datum::Set(const std::int32_t value, std::uint32_t index)
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
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::IntegerType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.i[index].std::int32_t::~int32_t();
			//	new (mData.i + index)std::int32_t(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const std::float_t value, std::uint32_t index)
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
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::FloatType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.f[index].std::float_t::~float_t();
			//	new (mData.f + index)std::float_t(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const glm::vec4& value, std::uint32_t index)
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
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::VectorType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.v[index].glm::vec4::~vec4();
			//	new (mData.v + index)glm::vec4(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const glm::mat4x4& value, std::uint32_t index)
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
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::MatrixType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.m[index].glm::mat4x4::~mat4x4();
			//	new (mData.m + index)glm::mat4x4(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const std::string& value, std::uint32_t index)
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
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::StringType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.s[index].std::string::~string();
			//	new (mData.s + index)std::string(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const GameplayFramework::RTTI* value, std::uint32_t index)
		{
			if (mDatumType != DatumType::PointerType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.r[index] = const_cast<GameplayFramework::RTTI*>(value);
			}
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
			//if (mDatumType == DatumType::UnknownType && IsEmpty() && index == 0)
			//{
			//	PushBack(value);
			//	return;
			//}
			//if (mDatumType != DatumType::PointerType)
			//{
			//	throw std::runtime_error("Improper set operation.");
			//}
			//if (mSize > index)
			//{
			//	mData.r[index] = const_cast<GameplayFramework::RTTI*>(value);
			//	return;
			//}
			//else if (mIsExternal)
			//{
			//	throw std::runtime_error("Out of bounds of the external array.");
			//}
			//PushBack(value);
		}

		void Datum::Set(const GameplayFramework::Scope* value, std::uint32_t index)
		{
			if (mDatumType != DatumType::TableType)
			{
				throw std::runtime_error("Improper set operation.");
			}
			if (mSize > index)
			{
				mData.sc[index] = const_cast<GameplayFramework::Scope*>(value);
			}
			else
			{
				throw std::runtime_error("Out of bounds of the external array.");
			}
		}


		bool Datum::operator==(const Datum& rhs) const
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
			// TODO Scope
			// In case of a Scope* type
			//else if (mDatumType == DatumType::TableType)
			//{
			//	for (std::uint32_t index = 0; index < mSize; ++index)
			//	{
			//		if (!(mData.sc[index]->Equals(rhs.mData.sc[index])))	return false;
			//	}
			//	return true;
			//}
			// In case of any other type
			std::uint32_t sizeOfElement = 0;
			if		(mDatumType == DatumType::IntegerType)	sizeOfElement = sizeof(std::int32_t);
			else if (mDatumType == DatumType::FloatType)	sizeOfElement = sizeof(std::float_t);
			else if (mDatumType == DatumType::MatrixType)	sizeOfElement = sizeof(glm::mat4x4);
			else if (mDatumType == DatumType::VectorType)	sizeOfElement = sizeof(glm::vec4);

			return (std::memcmp(mData.vp, rhs.mData.vp, sizeOfElement*mSize) == 0);
		}

		bool Datum::operator!=(const Datum & rhs) const
		{
			return !operator==(rhs);
		}


		bool Datum::operator==(const std::int32_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::IntegerType))
			{
				return false;
			}
			return (mData.i[0] == rhs);
		}

		bool Datum::operator==(const std::float_t rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::FloatType))
			{
				return false;
			}
			return (mData.f[0] == rhs);
		}

		bool Datum::operator==(const std::string& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::StringType))
			{
				return false;
			}
			return (mData.s[0] == rhs);
		}

		bool Datum::operator==(const glm::vec4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::VectorType))
			{
				return false;
			}
			return (mData.v[0] == rhs);
		}

		bool Datum::operator==(const glm::mat4x4& rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::MatrixType))
			{
				return false;
			}
			return (mData.m[0] == rhs);
		}

		bool Datum::operator==(const GameplayFramework::RTTI* rhs) const
		{
			if ((mSize != 1) || (mDatumType != DatumType::PointerType))
			{
				return false;
			}
			return (mData.r[0]->Equals(rhs));
		}

		// TODO Scope?

		bool Datum::operator!=(const std::int32_t rhs) const
		{
			return !operator==(rhs);
		}

		bool Datum::operator!=(const std::float_t rhs) const
		{
			return !operator==(rhs);
		}

		bool Datum::operator!=(const std::string& rhs) const
		{
			return !operator==(rhs);
		}

		bool Datum::operator!=(const glm::vec4& rhs) const
		{
			return !operator==(rhs);
		}

		bool Datum::operator!=(const glm::mat4x4& rhs) const
		{
			return !operator==(rhs);
		}

		bool Datum::operator!=(const GameplayFramework::RTTI* rhs) const
		{
			return !operator==(rhs);
		}

		// TODO Scope?

		void Datum::SetStorage(std::int32_t* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::IntegerType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.i = externalArray;
		}

		void Datum::SetStorage(std::float_t* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::FloatType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.f = externalArray;
		}

		void Datum::SetStorage(std::string* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::StringType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.s = externalArray;
		}

		void Datum::SetStorage(glm::vec4* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::VectorType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.v = externalArray;
		}

		void Datum::SetStorage(glm::mat4x4* externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::MatrixType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.m = externalArray;
		}

		void Datum::SetStorage(GameplayFramework::RTTI** externalArray, std::uint32_t numberOfElements)
		{
			if (mDatumType != DatumType::PointerType || numberOfElements == 0)
			{
				throw std::runtime_error("Datum cannot be assigned to an external array.");
			}
			// Clear and free the memory allocated to the datum previously
			if (!mIsExternal) ClearAndFree();
			// Update member variables
			mIsExternal = true;
			mSize = numberOfElements;
			mCapacity = numberOfElements;
			mData.r = externalArray;
		}

		// TODO Scope?

		Datum& Datum::operator=(const std::int32_t rhs)
		{
			if ((mDatumType != DatumType::IntegerType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;

			//if ((mDatumType != DatumType::IntegerType) && (mDatumType != DatumType::UnknownType))
			//{
			//	throw std::runtime_error("Illegal assignment operation.");
			//}
			//Set(rhs);
			//return *this;
		}

		Datum& Datum::operator=(const std::float_t rhs)
		{
			if ((mDatumType != DatumType::FloatType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		Datum& Datum::operator=(const std::string& rhs)
		{
			if ((mDatumType != DatumType::StringType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		Datum& Datum::operator=(const glm::vec4& rhs)
		{
			if ((mDatumType != DatumType::VectorType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		Datum& Datum::operator=(const glm::mat4x4& rhs)
		{
			if ((mDatumType != DatumType::MatrixType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		Datum& Datum::operator=(const GameplayFramework::RTTI* rhs)
		{
			if ((mDatumType != DatumType::PointerType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		Datum& Datum::operator=(const GameplayFramework::Scope* rhs)
		{
			if ((mDatumType != DatumType::TableType) && (mDatumType != DatumType::UnknownType))
			{
				throw std::runtime_error("Illegal assignment operation.");
			}
			if (mDatumType == DatumType::UnknownType && IsEmpty())
			{
				PushBack(rhs);
			}
			else
			{
				Set(rhs);
			}
			return *this;
		}

		// TODO Scope?

		GameplayFramework::Scope& Datum::operator[](std::uint32_t index)
		{
			return *(Get<GameplayFramework::Scope*>(index));
		}


		std::string Datum::ToString(std::uint32_t index)
		{
			if (mDatumType == DatumType::UnknownType || index >= mSize)
			{
				throw std::runtime_error("Invalid ToString operation.");
			}
			std::string stringToReturn;
			switch (mDatumType)
			{
			case DatumType::IntegerType:
				stringToReturn = std::to_string(Get<std::int32_t>(index));
				break;
			case DatumType::FloatType:
				stringToReturn = std::to_string(Get<std::float_t>(index));
				break;
			case DatumType::VectorType:
				stringToReturn = glm::to_string(Get<glm::vec4>(index));
				break;
			case DatumType::MatrixType:
				stringToReturn = glm::to_string(Get<glm::mat4x4>(index));
				break;
			case DatumType::TableType:
				break;
			case DatumType::StringType:
				stringToReturn = Get<std::string>(index);
				break;
			case DatumType::PointerType:
				stringToReturn = (Get<GameplayFramework::RTTI*>(index))->ToString();
				break;
			}
			return stringToReturn;
		}

		bool Datum::SetFromString(std::string& data, std::uint32_t index /* = 0 */)
		{
			if (mDatumType == DatumType::UnknownType)
			{
				throw std::runtime_error("Invalid set from string operation");
			}
			const char* stringToParse = data.c_str();
			switch (mDatumType)
			{
				// In case of an integer
			case DatumType::IntegerType:
			{
				std::int32_t value;
				if (sscanf_s(stringToParse, "%d", &value) != 1)
				{
					return false;
				}
				Set(value, index);
				return true;
			}
			// In case of a floating point number
			case DatumType::FloatType:
			{
				std::float_t value;
				if (sscanf_s(stringToParse, "%f", &value) != 1)
				{
					return false;
				}
				Set(value, index);
				return true;
			}
			// In case of a vector
			case DatumType::VectorType:
			{
				glm::vec4 vec;
				if (sscanf_s(stringToParse, "vec4(%f,%f,%f,%f)", &vec.x, &vec.y, &vec.z, &vec.w) != 4)
				{
					return false;
				}
				Set(vec, index);
				return true;
			}
			// In case of a matrix
			case DatumType::MatrixType:
			{
				glm::vec4 vec1;
				glm::vec4 vec2;
				glm::vec4 vec3;
				glm::vec4 vec4;
				if (sscanf_s(stringToParse, "mat4x4((%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f))", &vec1.x, &vec1.y, &vec1.z, &vec1.w, &vec2.x, &vec2.y, &vec2.z, &vec2.w, &vec3.x, &vec3.y, &vec3.z, &vec3.w, &vec4.x, &vec4.y, &vec4.z, &vec4.w) != 16)
				{
					return false;
				}
				glm::mat4x4 matToSet(vec1, vec2, vec3, vec4);
				Set(matToSet, index);
				return true;
			}

			case DatumType::TableType:
				return false;

				// In case of a string
			case DatumType::StringType:
				Set(data, index);
				return true;

			case DatumType::PointerType:
				break;
			}
			return false;
		}


		bool Datum::Remove(std::int32_t data)
		{
			if (mIsExternal || mDatumType != DatumType::IntegerType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.i[index] == data)
				{
					std::int32_t* destination = mData.i + index;
					std::int32_t* source = destination + 1;

					memmove_s(destination, sizeof(std::int32_t)*(mSize - index - 1) , source, sizeof(std::int32_t)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(std::float_t data)
		{
			if (mIsExternal || mDatumType != DatumType::FloatType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.f[index] == data)
				{
					std::float_t* destination = mData.f + index;
					std::float_t* source = destination + 1;

					memmove_s(destination, sizeof(std::float_t)*(mSize - index - 1), source, sizeof(std::float_t)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(std::string data)
		{
			if (mIsExternal || mDatumType != DatumType::StringType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.s[index] == data)
				{
					mData.s[index].std::string::~string();
					std::string* destination = mData.s + index;
					std::string* source = destination + 1;

					memmove_s(destination, sizeof(std::string)*(mSize - index - 1), source, sizeof(std::string)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(glm::vec4 data)
		{
			if (mIsExternal || mDatumType != DatumType::VectorType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.v[index] == data)
				{
					glm::vec4* destination = mData.v + index;
					glm::vec4* source = destination + 1;

					memmove_s(destination, sizeof(glm::vec4)*(mSize - index - 1), source, sizeof(glm::vec4)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(glm::mat4x4 data)
		{
			if (mIsExternal || mDatumType != DatumType::MatrixType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.m[index] == data)
				{
					glm::mat4x4* destination = mData.m + index;
					glm::mat4x4* source = destination + 1;

					memmove_s(destination, sizeof(glm::mat4x4)*(mSize - index - 1), source, sizeof(glm::mat4x4)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(GameplayFramework::RTTI* data)
		{
			if (mIsExternal || mDatumType != DatumType::PointerType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.r[index] == data)
				{
					GameplayFramework::RTTI** destination = mData.r + index;
					GameplayFramework::RTTI** source = destination + 1;

					memmove_s(destination, sizeof(GameplayFramework::RTTI**)*(mSize - index - 1), source, sizeof(GameplayFramework::RTTI**)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}

		bool Datum::Remove(GameplayFramework::Scope* data)
		{
			if (mIsExternal || mDatumType != DatumType::TableType)
			{
				throw std::runtime_error("Invalid remove operation.");
			}
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				if (mData.sc[index] == data)
				{
					GameplayFramework::Scope** destination = mData.sc + index;
					GameplayFramework::Scope** source = destination + 1;

					memmove_s(destination, sizeof(GameplayFramework::Scope**)*(mSize - index - 1), source, sizeof(GameplayFramework::Scope**)*(mSize - index - 1));
					mSize--;
					return true;
				}
			}
			return false;
		}


		template <>
		std::int32_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::IntegerType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.i[index];
		}

		template<>
		std::float_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::FloatType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.f[index];
		}

		template<>
		glm::vec4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::VectorType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.v[index];
		}

		template<>
		glm::mat4x4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::MatrixType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.m[index];
		}

		template<>
		std::string& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::StringType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.s[index];
		}

		template<>
		GameplayFramework::RTTI*& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::PointerType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.r[index];
		}

		template<>
		GameplayFramework::Scope*& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::TableType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.sc[index];
		}
	}
}