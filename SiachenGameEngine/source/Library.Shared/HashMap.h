#pragma once
#include <cstdint>
#include <utility>
#include "Vector.h"
#include "SList.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* A HashMap container which uses a vector of singly linked lists (for chaining) to store data.
		*/
		template<typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
		class HashMap
		{

		public:
			/**
			* An Iterator class for the HashMap container.
			*/
			class Iterator
			{

			};

			HashMap(std::uint32_t numberOfBuckets);
			~HashMap();

		private:
			typedef std::pair<TKey, TData> PairType;
			typedef SList<PairType> ChainType;
			typedef Vector<ChainType> BucketType;

			BucketType mMapBuckets;
		};

		template<typename TKey>
		class DefaultHash
		{
			std::uint32_t operator()(const TKey &key)
			{
				return std::uint32_t();
			}
		};
	}
}

#include "HashMap.inl"