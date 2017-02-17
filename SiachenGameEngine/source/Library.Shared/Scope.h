#pragma once

#include "RTTI.h"

#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Scope final : public RTTI
		{
			RTTI_DECLARATIONS(Scope, RTTI)
			
		private:
			typedef std::pair<std::string, Containers::Datum> StringDatumPair;
			typedef Containers::HashMap<std::string, Containers::Datum> TableType;
			typedef Containers::Vector<StringDatumPair*> VectorType;
			
			TableType mTableHashmap;

			VectorType mIndexVector;

			Scope* mParent;

		public:
			// TODO Pick a default value
			Scope(std::uint32_t initialCapacity = 13);
			// TODO Delete all the children scopes
			~Scope() = default;

			// TODO Caching of insertion
			Containers::Datum& Append(const std::string& key);

			Scope& AppendScope(const std::string& key);

			Containers::Datum* Find(const std::string& key) const;

			Containers::Datum* Search(const std::string& key, Scope** owningScope = nullptr) const;

			// TODO Write logic
			virtual bool Equals(const RTTI* rhs) const override;
			// TODO Write logic
			virtual std::string ToString() const override;
			// TODO Check if const version is logical
			Containers::Datum& operator[](const std::string& key);

			Containers::Datum& operator[](const std::uint32_t index);

			const Containers::Datum& operator[](const std::uint32_t index) const;
		};
	}
}