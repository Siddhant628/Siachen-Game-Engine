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
			
			Containers::HashMap<std::string, Containers::Datum> mTable;

			Containers::Vector<StringDatumPair*> mIndexVector;

			Scope* mParent;

		public:
			// TODO Pick a default value
			Scope(std::uint32_t initialCapacity = 13);
			// TODO Delete all the children scopes
			~Scope();

			Containers::Datum& Append(const std::string key);

			// TODO Write logic
			virtual bool Equals(const RTTI* rhs) const override;
			// TODO Write logic
			virtual std::string ToString() const override;
		};
	}
}