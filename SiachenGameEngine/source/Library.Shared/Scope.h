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

			virtual bool Is(const std::string& name) const;
		};
	}
}