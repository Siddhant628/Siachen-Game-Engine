#include "pch.h"
#include "Scope.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Scope)

		Scope::Scope(std::uint32_t initialCapacity /* = 13 */) : mTable(initialCapacity), mIndexVector(initialCapacity)
		{
			if (initialCapacity == 0)
			{
				throw std::runtime_error("Cannot create a scope of size 0.");
			}
		}

		Scope::~Scope()
		{

		}

		//Containers::Datum& Scope::Append(const std::string key)
		//{
		//	// Check if the pair is already present in the scope

		//}

		bool Scope::Equals(const RTTI* rhs) const
		{
			UNREFERENCED_PARAMETER(rhs);
			return true;
		}

		std::string Scope::ToString() const
		{
			return "SCOPE";
		}
	}
}

