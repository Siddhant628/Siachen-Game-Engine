#include "pch.h"
#include "Attributed.h"

#include "Datum.h"
#include "RTTI.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Attributed)
			Attributed::Attributed() : prescribedAttributeCount(0), prescribedAttributesAssigned(false)
		{

		}

		void Attributed::Populate()
		{
			// TODO Check if this append happens for parent or for child.
			Append("this") = static_cast<RTTI*>(this);
			++prescribedAttributeCount;
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute)
		{
			if (isPrescribedAttribute)
			{
				if (prescribedAttributesAssigned)
				{
					throw std::runtime_error("Cannot insert new prescribed attributes.");
				}
				if ((Find(attributeName) == nullptr))
				{
					++prescribedAttributeCount;
					// TODO Add to vector for prescribed attributes
				}
			}
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::IntegerType);
			datum.SetStorage(const_cast<std::int32_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue, bool isPrescribedAttribute)
		{
			if (isPrescribedAttribute)
			{
				if (prescribedAttributesAssigned)
				{
					throw std::runtime_error("Cannot insert new prescribed attributes.");
				}
				if ((Find(attributeName) == nullptr))
				{
					++prescribedAttributeCount;
					// TODO Add to vector for prescribed attributes
				}
				Datum& datum = Append(attributeName);
				datum.Set(attributeValue);
			}
		}

		void Attributed::SetPrescribedAttributesAssigned()
		{
			prescribedAttributesAssigned = true;
		}

	}
}
