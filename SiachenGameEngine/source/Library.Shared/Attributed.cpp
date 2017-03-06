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

		Attributed::Attributed() : mPrescribedAttributeCount(0)//, prescribedAttributesAssigned(false)
		{
			Populate();
			UpdatePrescribedAttributeCache();
		}

		//void Attributed::ValidatePrescribedAttribute(const std::string& attributeName)
		//{
		//	//if (prescribedAttributesAssigned)
		//	//{
		//	//	throw std::runtime_error("Cannot insert new prescribed attributes.");
		//	//}
		//	if ((Find(attributeName) == nullptr))
		//	{
		//		++mPrescribedAttributeCount;
		//		UpdatePrescribedAttributeCache(TypeIdInstance(), attributeName);
		//	}
		//}

		//void Attributed::UpdatePrescribedAttributeCache(const std::uint64_t& attributedClassId, const std::string& attributeName)
		//{
		//	CacheHashmapType::Iterator it = sPrescribedAttributeCache.Find(attributedClassId);
		//	if (it != sPrescribedAttributeCache.end())
		//	{
		//		if ((*it).second.Find(attributeName) == (*it).second.end())
		//		{
		//			(*it).second.PushBack(attributeName);
		//		}
		//	}
		//	else
		//	{
		//		Vector<std::string> cacheVector;
		//		cacheVector.PushBack(attributeName);
		//		std::pair<std::uint64_t, Containers::Vector<std::string>> pair(TypeIdInstance(), cacheVector);
		//		sPrescribedAttributeCache.Insert(pair);
		//	}
		//}

		void Attributed::Populate()
		{
			//AddInternalAttribute("this", static_cast<RTTI*>(this), true);
			AddInternalAttribute("this", static_cast<RTTI*>(this));
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues/*, bool isPrescribedAttribute*/)
		{
			//if (isPrescribedAttribute)
			//{
			//	ValidatePrescribedAttribute(attributeName);
			//}
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::IntegerType);
			datum.SetStorage(const_cast<std::int32_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddExternalAttribute(const std::string& attributeName, const std::float_t* externalAttribute, std::uint32_t numberOfValues/*, bool isPrescribedAttribute*/)
		{
			Datum& datum = Append(attributeName);
			datum.SetType(DatumType::FloatType);
			datum.SetStorage(const_cast<std::float_t*>(externalAttribute), numberOfValues);
		}

		void Attributed::AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue/*, bool isPrescribedAttribute*/)
		{
			//if (isPrescribedAttribute)
			//{
			//	ValidatePrescribedAttribute(attributeName);
			//}
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

		//void Attributed::SetPrescribedAttributesAssigned()
		//{
		//	prescribedAttributesAssigned = true;
		//}

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

		bool Attributed::IsAuxillaryAttribute(const std::string& attributeName) const
		{
			if (IsAttribute(attributeName) && !IsPrescribedAttribute(attributeName))
			{
				return true;
			}
			return false;
		}

		Containers::Datum& Attributed::AppendAuxillaryAttribute(const std::string& attributeName)
		{
			if (IsPrescribedAttribute(attributeName))
			{
				throw std::runtime_error("An prescribed attribute with the same name is already present in the scope.");
			}
			Datum& datum = Append(attributeName);
			return datum;
		}

		std::uint32_t Attributed::AuxillaryBegin() const
		{
			return mPrescribedAttributeCount;
		}

		void Attributed::UpdatePrescribedAttributeCache()
		{
			//// Set prescribed attribute count since prescribed attributes have been inserted
			//mPrescribedAttributeCount = mTableHashmap.Size();
			//// Insert classID, Vector pair into static hashmap if required
			//CacheHashmapType::Iterator itCache = sPrescribedAttributeCache.Find(TypeIdInstance());
			//if (itCache == sPrescribedAttributeCache.end())
			//{
			//	std::pair<std::uint64_t, Containers::Vector<std::string>> pair(TypeIdInstance(), Vector<std::string>());
			//	sPrescribedAttributeCache.Insert(pair);
			//	itCache = sPrescribedAttributeCache.Find(TypeIdInstance());
			//}
			//// Fill the prescribed attributes vector if it is empty
			//TableType::Iterator itTable = mTableHashmap.begin();
			//for (; itTable != mTableHashmap.end(); ++itTable)
			//{
			//	std::string attributeName = (*itTable).first;
			//	if ((*itCache).second.Find(attributeName) == (*itCache).second.end())
			//	{
			//		(*itCache).second.PushBack(attributeName);
			//	}
			//}

			Vector<std::string> attributeList;
			GetKeys(attributeList);
			// Set prescribed attribute count since prescribed attributes have been inserted
			mPrescribedAttributeCount = attributeList.Size();
			// Insert classID, Vector pair into static hashmap if required
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
	}

}