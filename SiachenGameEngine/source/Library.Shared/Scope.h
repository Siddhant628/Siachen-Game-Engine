#pragma once

#include "RTTI.h"

#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Scope : public RTTI
		{
		private:
			typedef std::pair<std::string, Containers::Datum> StringDatumPair;

			Containers::HashMap<std::string, Containers::Datum> mTable;
			Containers::Vector<StringDatumPair*> mIndexCache;

		public:

		};
	}
}