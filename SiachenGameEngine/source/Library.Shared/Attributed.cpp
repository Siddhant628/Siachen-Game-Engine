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
			Populate();
		}

		void Attributed::ValidatePrescribedAttribute(const std::string& attributeName)
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

		void Attributed::Populate()
		{
			AddInternalAttribute("this", static_cast<RTTI*>(this), true);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute)
		{
			if (isPrescribedAttribute)
			{
				ValidatePrescribedAttribute(attributeName);
			}
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::IntegerType);
			datum.SetStorage(const_cast<std::int32_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue, bool isPrescribedAttribute)
		{
			if (isPrescribedAttribute)
			{
				ValidatePrescribedAttribute(attributeName);
			}
			Datum& datum = Append(attributeName);
			if (datum.IsEmpty())
			{
				datum.PushBack(attributeValue);
			}
			else
			{
				datum.Set(attributeValue);
			}
		}

		void Attributed::SetPrescribedAttributesAssigned()
		{
			prescribedAttributesAssigned = true;
		}

		std::uint32_t Attributed::AuxillaryBegin()
		{
			return prescribedAttributeCount;
		}

		bool Attributed::IsAttribute(const std::string& attributeName)
		{
			return (Find(attributeName) != nullptr);
		}

		bool Attributed::IsPrescribedAttribute(const std::string & attributeName)
		{
			UNREFERENCED_PARAMETER(attributeName);
			return false;
		}

		bool Attributed::IsAuxillaryAttribute(const std::string & attributeName)
		{
			if (IsAttribute(attributeName) && !IsPrescribedAttribute(attributeName))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}
}
