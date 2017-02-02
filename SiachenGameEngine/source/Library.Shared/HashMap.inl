#include "HashMap.h"
#include <cstdint>

namespace SiachenGameEngine
{
	namespace Containers
	{
		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t numberOfBuckets) : mMapBuckets(BucketType(numberOfBuckets))
		{

		}
		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::~HashMap()
		{

		}
	}
}