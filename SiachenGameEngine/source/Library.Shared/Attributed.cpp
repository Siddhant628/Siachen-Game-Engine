#include "pch.h"
#include "Attributed.h"

#include "Datum.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Attributed)

		Containers::HashMap<std::uint64_t, Containers::Vector<std::string>> Attributed::prescribedAttributeCache;
		
		Attributed::Attributed() : prescribedAttributeCount(0), prescribedAttributesAssigned(false)
		{
			// TODO Remove
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
				UpdatePrescribedAttributeCache(TypeIdInstance(), attributeName);
			}
		}

		void Attributed::UpdatePrescribedAttributeCache(const std::uint64_t& attributedClassId, const std::string& attributeName)
		{
			HashMap<std::uint64_t, Containers::Vector<std::string>>::Iterator it = prescribedAttributeCache.Find(attributedClassId);
			if (it != prescribedAttributeCache.end())
			{
				if ((*it).second.Find(attributeName) == (*it).second.end())
				{
					(*it).second.PushBack(attributeName);
				}
			}
			else
			{
				Vector<std::string> cacheVector;
				cacheVector.PushBack(attributeName);
				std::pair<std::uint64_t, Containers::Vector<std::string>> pair(TypeIdInstance(), cacheVector);
				prescribedAttributeCache.Insert(pair);
			}
		}

		void Attributed::ClearCacheHashmap()
		{
			prescribedAttributeCache.Clear();
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

		bool Attributed::IsPrescribedAttribute(const std::string& attributeName)
		{
			UNREFERENCED_PARAMETER(attributeName);
			return false;
		}

		bool Attributed::IsAuxillaryAttribute(const std::string& attributeName)
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

		Containers::Datum& Attributed::AppendAuxillaryAttribute(const std::string& attributeName)
		{
			if (IsPrescribedAttribute(attributeName))
			{
				throw std::runtime_error("An prescribed attribute with the same name is already present in the scope.");
			}
			return Append(attributeName);
		}
}

	}