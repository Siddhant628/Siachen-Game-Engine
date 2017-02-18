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

			void DeepCopyScope(const Scope& rhs);

		public:
			Scope(std::uint32_t initialCapacity = 13);

			Scope(const Scope& rhs);

			Scope& operator=(const Scope& rhs);

			~Scope();

			Containers::Datum& Append(const std::string& key);

			Scope& AppendScope(const std::string& key);

			Containers::Datum* Find(const std::string& key) const;

			Containers::Datum* Search(const std::string& key, Scope** owningScope = nullptr) const;

			Scope* GetParent() const;

			virtual bool Equals(const RTTI* rhs) const override;
			// TODO Write logic
			virtual std::string ToString() const override;
			
			Containers::Datum& operator[](const std::string& key);

			Containers::Datum& operator[](const std::uint32_t index);

			const Containers::Datum& operator[](const std::uint32_t index) const;

			bool Orphan();

			void Adopt(Scope& childToAdopt, const std::string& nameOfChild);
		
			void Clear();

			bool operator==(const Scope& rhs) const;

			bool operator!=(const Scope& rhs) const;
		};
	}
}