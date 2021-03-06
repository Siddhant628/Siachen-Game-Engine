#include "pch.h"
#include "Scope.h"
#include "Datum.h"
#include <string>
#include <sstream>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Scope)

		void Scope::DeepCopyScope(const Scope& rhs)
		{
			VectorType::Iterator end = rhs.mIndexVector.end();
			for (VectorType::Iterator it = rhs.mIndexVector.begin(); it != end; ++it)
			{
				Datum& datum = (*it)->second;
				if (datum.Type() == DatumType::TableType)
				{
					for (std::uint32_t index = 0; index < datum.Size(); ++index)
					{
						Scope* scope = new Scope(datum[index]);
						Adopt(*scope, (*it)->first);
					}
				}
				else
				{
					TableType::Iterator insertedItem = mTableHashmap.Insert(*(*it));
					mIndexVector.PushBack(&*insertedItem);
				}
			}
		}

		Scope::Scope(std::uint32_t initialCapacity /* = 13 */) : mTableHashmap(initialCapacity), mParent(nullptr)
		{
			if (initialCapacity == 0)
			{
				throw std::runtime_error("Cannot create a scope of size 0.");
			}
		}

		Scope::Scope(const Scope& rhs) : mParent(nullptr)
		{
			DeepCopyScope(rhs);
		}

		Scope& Scope::operator=(const Scope& rhs)
		{
			if (this != &rhs)
			{
				Clear();
				DeepCopyScope(rhs);
			}
			return *this;
		}

		Scope::~Scope()
		{
			Clear();
		}

		Datum& Scope::Append(const std::string& key)
		{
			TableType::Iterator it = mTableHashmap.Find(key);
			// If the pair is not present in the scope
			if (it == mTableHashmap.end())
			{
				StringDatumPair pair(key, Datum());
				// Update the table and vector
				it = mTableHashmap.Insert(pair);
				mIndexVector.PushBack(&*it);
			}
			return (*it).second;
		}

		Scope& Scope::AppendScope(const std::string& key)
		{
			bool pairInserted;

			// Check if a datum of another type is present for the given key
			TableType::Iterator it = mTableHashmap.Find(key);
			if ((it != mTableHashmap.end()) && (it->second.Type() != DatumType::TableType))
			{
				throw std::runtime_error("Invalid key for appending a scope.");
			}
			// Create the scope to append
			Scope* scope = new Scope;
			scope->mParent = this;
			// Try inserting the pair into the scope
			it = mTableHashmap.Insert(make_pair(key, Datum()), pairInserted);
			it->second.PushBack(*scope);
			// Update index vector for the scope
			if (pairInserted)
			{
				mIndexVector.PushBack(&*it);
			}
			return *scope;
		}

		Datum* Scope::Find(const std::string& key) const
		{
			Containers::Datum* datum = nullptr;
			TableType::Iterator it = mTableHashmap.Find(key);
			if (it != mTableHashmap.end())
			{
				datum = &((*it).second);
			}
			return datum;
		}

		Datum* Scope::Search(const std::string& key, Scope** owningScope) const
		{
			Scope* searchScope = const_cast<Scope*>(this);
			Containers::Datum* foundDatum = nullptr;

			while (searchScope != nullptr)
			{
				foundDatum = searchScope->Find(key);
				if (foundDatum != nullptr)
				{
					if (owningScope != nullptr)
					{
						*owningScope = searchScope;
					}
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
			Scope* rhsScope = rhs->As<Scope>();
			if (rhsScope == nullptr)
			{
				return false;
			}
			return (operator==(*rhsScope));
		}

		std::string Scope::ToString() const
		{
			std::stringstream stream;
			stream << "Scope(" << mTableHashmap.Size() << ")";
			return stream.str();
		}

		Datum& Scope::operator[](const std::string& key)
		{
			return Append(key);
		}

		Datum& Scope::operator[](const std::uint32_t index)
		{
			return (*mIndexVector[index]).second;
		}

		const Datum& Scope::operator[](const std::uint32_t index) const
		{
			return (*mIndexVector[index]).second;
		}

		bool Scope::Orphan()
		{
			bool valueToReturn = false;
			if (mParent != nullptr)
			{
				Scope* parentScope = mParent;
				TableType::Iterator it = parentScope->mTableHashmap.begin();
				TableType::Iterator end = parentScope->mTableHashmap.end();

				for (; it != end; ++it)
				{
					if ((it->second).Type() == DatumType::TableType)
					{
						if ((it->second).Remove(*this))
						{
							mParent = nullptr;
							valueToReturn = true;
							break;
						}
					}
				}
			}
			return valueToReturn;
		}

		void Scope::Adopt(Scope& childToAdopt, const std::string& nameOfChild)
		{
			// Check if nameOfChild is a valid key
			TableType::Iterator it = mTableHashmap.Find(nameOfChild);
			if ((it != mTableHashmap.end()) && (it->second.Type() != DatumType::TableType))
			{
				throw std::runtime_error("Invalid key for adopting.");
			}
			// Prevent user from adopting this scope itself
			if (this == &childToAdopt)
			{
				throw std::runtime_error("Scope cannot adopt itself.");
			}
			childToAdopt.Orphan();
			childToAdopt.mParent = this;
			Append(nameOfChild).PushBack(childToAdopt);
		}

		void Scope::Clear()
		{
			VectorType::Iterator end = mIndexVector.end();

			for (VectorType::Iterator it = mIndexVector.begin(); it != end; ++it)
			{
				Datum& datum = (*it)->second;
				if (datum.Type() == DatumType::TableType)
				{
					std::uint32_t size = datum.Size();
					for (std::uint32_t i = 0; i < size; ++i)
					{
						delete datum.Get<Scope*>(i);
					}
				}
			}
			mTableHashmap.Clear();
			mIndexVector.Clear();
		}

		bool Scope::operator==(const Scope& rhs) const
		{
			bool valueToReturn = true;
			if (mIndexVector.Size() != rhs.mIndexVector.Size())
			{
				valueToReturn = false;
			}
			else
			{
				std::uint32_t size = mIndexVector.Size();
				for (std::uint32_t index = 0; index < size; ++index)
				{
					if (*mIndexVector[index] != *rhs.mIndexVector[index])
					{
						valueToReturn = false;
						break;
					}
				}
			}
			return valueToReturn;
		}

		bool Scope::operator!=(const Scope& rhs) const
		{
			return !(operator==(rhs));
		}

		void Scope::GetKeys(Vector<std::string>& keysVector) const
		{
			keysVector.Clear();

			TableType::Iterator it = mTableHashmap.begin();
			TableType::Iterator itEnd = mTableHashmap.end();

			for (; it != itEnd; ++it)
			{
				keysVector.PushBack((*it).first);
			}
		}
	}
}

