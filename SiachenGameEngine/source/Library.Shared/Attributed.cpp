#include "pch.h"
#include "Attributed.h"

#include "Datum.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Attributed)

		Containers::HashMap<std::uint64_t, Containers::Vector<std::string>> Attributed::sPrescribedAttributeCache;

		Attributed::Attributed() : mPrescribedAttributeCount(0)
		{
			Populate();
			UpdatePrescribedAttributeCache();
		}


		void Attributed::Populate()
		{
			AddInternalAttribute("this", static_cast<RTTI*>(this));
		}

		void Attributed::UpdatePrescribedAttributeCache()
		{
			Vector<std::string> attributeList;
			GetKeys(attributeList);
			// Update prescribed attribute count
			mPrescribedAttributeCount = attributeList.Size();
			// Insert <classID, Vector of strings> pair into static hashmap if absent
			CacheHashmapType::Iterator itCache = sPrescribedAttributeCache.Find(TypeIdInstance());
			if (itCache == sPrescribedAttributeCache.end())
			{
				std::pair<std::uint64_t, Containers::Vector<std::string>> pair(TypeIdInstance(), Vector<std::string>());
				sPrescribedAttributeCache.Insert(pair);
				itCache = sPrescribedAttributeCache.Find(TypeIdInstance());
			}
			// Fill the prescribed attributes vector if it is empty
			for (std::uint32_t i = 0; i < mPrescribedAttributeCount; ++i)
			{
				std::string attributeName = attributeList.At(i);
				if ((*itCache).second.Find(attributeName) == (*itCache).second.end())
				{
					(*itCache).second.PushBack(attributeName);
				}
			}
		}


		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::IntegerType);
			datum.SetStorage(const_cast<std::int32_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::float_t* externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::FloatType);
			datum.SetStorage(const_cast<std::float_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::string* externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::StringType);
			datum.SetStorage(const_cast<std::string*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const glm::vec4* externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::VectorType);
			datum.SetStorage(const_cast<glm::vec4*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const glm::mat4x4* externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::MatrixType);
			datum.SetStorage(const_cast<glm::mat4x4*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const Scope** externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::TableType);
			datum.SetStorage(const_cast<Scope**>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const RTTI** externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::PointerType);
			datum.SetStorage(const_cast<RTTI**>(externalAttribute), numberOfValues);
		}


		void Attributed::AddInternalAttribute(const std::string& attributeName, const std::int32_t attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const std::float_t attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const std::string& attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const glm::vec4& attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const glm::mat4x4& attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const Scope* attributeValue)
		{
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue)
		{
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


		bool Attributed::IsAttribute(const std::string& attributeName) const
		{
			return (Find(attributeName) != nullptr);
		}

		bool Attributed::IsPrescribedAttribute(const std::string& attributeName) const
		{
			CacheHashmapType::Iterator it = sPrescribedAttributeCache.Find(TypeIdInstance());

			Vector<std::string>& attributeList = (*it).second;
			if (attributeList.Find(attributeName) != attributeList.end())
			{
				return true;
			}
			return false;
		}

		bool Attributed::IsAuxiliaryAttribute(const std::string& attributeName) const
		{
			if (IsAttribute(attributeName) && !IsPrescribedAttribute(attributeName))
			{
				return true;
			}
			return false;
		}


		Containers::Datum& Attributed::AppendAuxiliaryAttribute(const std::string& attributeName)
		{
			if (IsPrescribedAttribute(attributeName))
			{
				throw std::runtime_error("An prescribed attribute with the same name is already present in the scope.");
			}
			Datum& datum = Append(attributeName);
			return datum;
		}

		std::uint32_t Attributed::AuxiliaryBegin() const
		{
			return mPrescribedAttributeCount;
		}
	}

}