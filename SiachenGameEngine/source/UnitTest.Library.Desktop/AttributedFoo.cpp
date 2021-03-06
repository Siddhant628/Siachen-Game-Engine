#include "pch.h"

#include "AttributedFoo.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(AttributedFoo)

		AttributedFoo::AttributedFoo()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		AttributedFoo::AttributedFoo(const AttributedFoo& rhs) : Attributed(rhs)
		{

			(*this)["mInteger"].SetStorage(&mInteger, 1U);
			(*this)["mInteger"].Set(rhs.GetInteger());

			SetAuxillaryBegin(rhs.AuxiliaryBegin());
		}

		AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
		{
			if (this != &rhs)
			{
				Attributed::operator=(rhs);

				(*this)["mInteger"].SetStorage(&mInteger, 1U);
				(*this)["mInteger"].Set(rhs.GetInteger());

				SetAuxillaryBegin(rhs.AuxiliaryBegin());
			}
			return *this;
		}

		void AttributedFoo::Populate()
		{
			AddExternalAttribute("mInteger", &mInteger, 1U);
		}

		std::int32_t AttributedFoo::GetInteger() const
		{
			return mInteger;
		}

		void AttributedFoo::SetInteger(std::int32_t value)
		{
			mInteger = value;
		}
	}
}
