#include "Scope.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
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
	}
}

