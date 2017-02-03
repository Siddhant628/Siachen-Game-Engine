#pragma once
#include <cstdint>
#include <utility>
#include <string>
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

		private:
			typedef std::pair<TKey, TData> PairType;
			typedef SList<PairType> ChainType;
			typedef Vector<ChainType> BucketType;
			/**
			* The vector containing all the data of the hash map.
			*/
			BucketType mHashmap;

		public:
			/**
			* An Iterator class for the HashMap container.
			*/
			class Iterator
			{

			private:
				BucketType* mOwnerMap;
				std::uint32_t mBucketIndex;
				typename SList<PairType>::Iterator mListIterator;
			
			public:
				Iterator();
			};
			/**
			* Constructor which makes an initialized vector of specified size to store value-type pairs.
			* @param numberOfBuckets The number of buckets the initialized hash map will have (default value is 13)
			*/
			explicit HashMap(std::uint32_t numberOfBuckets = 13);

			~HashMap();
		};

		/**
		* Default hash functor to be used by the hash map.
		*/
		template<typename TKey>
		class DefaultHash
		{
		public:
			std::uint32_t operator()(const TKey &key) const;
		};
		/**
		* Default hash functor's specialization for char*.
		*/
		template<>
		class DefaultHash <char*>
		{
		public:
			std::uint32_t operator()(const char* &key) const;
		};
		/**
		* Default hash functor's specialization for string class.
		*/
		template<>
		class DefaultHash <std::string>
		{
		public:
			std::uint32_t operator()(const std::string &key) const;
		};
	}
}

#include "HashMap.inl"