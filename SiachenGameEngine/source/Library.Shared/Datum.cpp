#include "Datum.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		// TODO Initialize in init line, add enum type
		Datum::Datum() : mSize(0), mCapacity(0), mDatumType(DatumType::UnknownType), mIsExternal(false)
		{
			mData.vp = nullptr;
		}

		// TODO Implement
		//Datum::Datum(const Datum& rhs)
		//{
		//	UNREFERENCED_PARAMETER(rhs);
		//}

		// TODO Implement - 4 cases
		//Datum& Datum::operator=(const Datum& rhs)
		//{
		//	UNREFERENCED_PARAMETER(rhs);
		//	return *this;
		//}

		// TODO Implement
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

		DatumType Datum::Type() const
		{
			return mDatumType;
		}

		bool Datum::SetType(DatumType setType)
		{
			if (mDatumType != DatumType::UnknownType)
			{
				return false;
			}
			mDatumType = setType;
			return true;
		}

		std::uint32_t Datum::Size() const
		{
			return mSize;
		}
	}
}