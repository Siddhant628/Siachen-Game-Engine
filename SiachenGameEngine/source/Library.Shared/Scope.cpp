#include "pch.h"
#include "Scope.h"
#include "Datum.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Scope)

		Scope::Scope(std::uint32_t initialCapacity /* = 13 */) : mTableHashmap(initialCapacity), mIndexVector(initialCapacity), mParent(nullptr)
		{
			if (initialCapacity == 0)
			{
				throw std::runtime_error("Cannot create a scope of size 0.");
			}
		}

		//Scope::~Scope()
		//{

		//}

		Containers::Datum& Scope::Append(const std::string& key)
		{
			TableType::Iterator it =  mTableHashmap.Find(key);
			// If the pair is not present in the scope
			if(it == mTableHashmap.end())
			{
				StringDatumPair pair(key, Containers::Datum());
				// Update the table and vector
				it = mTableHashmap.Insert(pair);
				mIndexVector.PushBack(&*it);
			}
			return (*it).second;
		
		}

		Scope& Scope::AppendScope(const std::string& key)
		{
			Containers::Datum datum;
			// Create the scope to append
			Scope* scope = new Scope;
			scope->mParent = this;
			// Check if the key is present in the table
			TableType::Iterator it = mTableHashmap.Find(key);
			if(it == mTableHashmap.end())
			{
				datum.PushBack(scope);
				StringDatumPair pair(key, datum);
				// Update the table and vector
				it = mTableHashmap.Insert(pair);
				mIndexVector.PushBack(&*it);
			}
			else
			{
				(it->second).PushBack(scope);
			}
			return *scope;
		}

		Containers::Datum* Scope::Find(const std::string& key) const
		{
			Containers::Datum* datum = nullptr;
			TableType::Iterator it = mTableHashmap.Find(key);
			if (it != mTableHashmap.end())
			{
				datum = &((*it).second);
			}
			return datum;
		}

		Containers::Datum* Scope::Search(const std::string& key, Scope** owningScope) const
		{
			Scope* searchScope = const_cast<Scope*>(this);
			Containers::Datum* foundDatum = nullptr;

			while (searchScope != nullptr)
			{
				foundDatum = searchScope->Find(key);
				if (foundDatum != nullptr)
				{
					owningScope = &searchScope;
					break;
				}
				searchScope = searchScope->mParent;
			}
			return foundDatum;
		}

		Scope* Scope::GetParent() const
		{
			return mParent;
		}

		bool Scope::Equals(const RTTI* rhs) const
		{
			UNREFERENCED_PARAMETER(rhs);
			return true;
		}

		std::string Scope::ToString() const
		{
			return "SCOPE";
		}

		Containers::Datum& Scope::operator[](const std::string& key)
		{
			return Append(key);
		}

		Containers::Datum& Scope::operator[](const std::uint32_t index)
		{
			return (*mIndexVector[index]).second;
		}

		const Containers::Datum& Scope::operator[](const std::uint32_t index) const
		{
			return (*mIndexVector[index]).second;
		}

	}
}

