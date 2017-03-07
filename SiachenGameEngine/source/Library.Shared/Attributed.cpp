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
			UpdatePrescribedAttributeInfo();
		}


		void Attributed::Populate()
		{
			AddInternalAttribute("this", static_cast<RTTI*>(this));
		}

		void Attributed::UpdatePrescribedAttributeInfo()
		{

			Vector<std::string> attributeList;
			GetKeys(attributeList);
			std::uint64_t instanceId = TypeIdInstance();

			// Update prescribed attribute count
			mPrescribedAttributeCount = attributeList.Size();

			// Check if the static hashmap has attribute list for this type
			if(!sPrescribedAttributeCache.ContainsKey(instanceId))
			{
				// Insert <classID, Vector of strings> pair into static hashmap
				std::pair<std::uint64_t, Containers::Vector<std::string>> pair(instanceId, Vector<std::string>());
				sPrescribedAttributeCache.Insert(pair);
				CacheHashmapType::Iterator itCache = sPrescribedAttributeCache.Find(instanceId);
				// Fill the prescribed attributes vector if it is empty
				for (std::uint32_t i = 0; i < mPrescribedAttributeCount; ++i)
				{
					std::string attributeName = attributeList.At(i);
					(*itCache).second.PushBack(attributeName);
				}
			}
		}


		void Attributed::AddExternalAttribute(const std::string& attributeName, std::int32_t* const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::IntegerType);
			datum.SetStorage(externalAttribute, numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, std::float_t* const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::FloatType);
			datum.SetStorage(externalAttribute, numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, std::string* const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::StringType);
			datum.SetStorage(externalAttribute, numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, glm::vec4* const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::VectorType);
			datum.SetStorage(externalAttribute, numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, glm::mat4x4* const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::MatrixType);
			datum.SetStorage(externalAttribute, numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, RTTI** const externalAttribute, std::uint32_t numberOfValues)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::PointerType);
			datum.SetStorage(externalAttribute, numberOfValues);
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

		void Attributed::AddInternalAttribute(const std::string& attributeName, Scope* const attributeValue)
		{
			Datum* scopeDatum = Find(attributeName);
			if (scopeDatum == nullptr)
			{
				Scope& scope = AppendScope(attributeName);
				scope = *attributeValue;
			}
		}

		void Attributed::AddInternalAttribute(const std::string& attributeName, RTTI* const attributeValue)
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