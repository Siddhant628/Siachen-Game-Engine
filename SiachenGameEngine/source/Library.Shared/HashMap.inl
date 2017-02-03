#include "HashMap.h"
#include <cstdint>

namespace SiachenGameEngine
{
	namespace Containers
	{
		// Iterator constructors

		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::Iterator::Iterator() : mOwnerMap(nullptr), mBucketIndex(0)
		{

		}
		
		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator &it) : mOwnerMap(it.mOwnerMap), mBucketIndex(it.mBucketIndex), mListIterator(it.mListIterator)
		{

		}

		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(HashMap* ownerMap, std::uint32_t bucketIndex, typename SList<PairType>::Iterator listIterator) : mOwnerMap(ownerMap), mBucketIndex(bucketIndex), mListIterator(listIterator)
		{

		}

		// Iterator operations

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator &it)
		{
			it(this != &it)
			{
				mOwnerMap = it.mOwnerMap;
				mBucketIndex = it.mBucketIndex;
				mListIterator = it.mListIterator;
			}
			return *this;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator &it) const
		{
			return((mOwnerMap == it.mOwnerMap) && (mBucketIndex == it.mBucketIndex) && (mListIterator == it.mListIterator));
		}

		template<typename TKey, typename TData, typename HashFunctor>
		bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator &it) const
		{
			return((mOwnerMap != it.mOwnerMap) || (mBucketIndex != it.mBucketIndex) || (mListIterator != it.mListIterator));
		}

		// HashMap constructors

		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t numberOfBuckets) : mHashmap(BucketType(numberOfBuckets))
		{

		}
		
		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::~HashMap()
		{

		}

		// Hashing functions

		template<typename TKey>
		std::uint32_t DefaultHash<TKey>::operator()(const TKey &key) const
		{
			std::uint32_t numberOfBytes = sizeof(key);
			const std::uint8_t* byteOfKey = reinterpret_cast<const std::uint8_t*>(&key);
			std::uint32_t hashValue = 0;

			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + byteOfKey[i];
			}
			return hashValue;
		}

		std::uint32_t DefaultHash<char*>::operator()(const char* &key) const
		{
			std::uint32_t numberOfBytes = static_cast<std::uint32_t>(strlen(key));
			std::uint32_t hashValue = 0;

			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + key[i];
			}
			return hashValue;
		}

		std::uint32_t DefaultHash<std::string>::operator()(const std::string &key) const
		{
			const char* str = key.c_str();
			std::uint32_t numberOfBytes = static_cast<std::uint32_t>(strlen(str));
			std::uint32_t hashValue = 0;

			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + key[i];
			}
			return hashValue;
		}

		std::uint32_t DefaultHash<HelperClasses::Foo>::operator()(const HelperClasses::Foo &foo) const
		{
			const std::int32_t value = foo.GetValue();
			const std::uint8_t* byteOfValue = reinterpret_cast<const std::uint8_t*>(&value);
			std::uint32_t numberOfBytes = sizeof(value);
			std::uint32_t hashValue = 0;
			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + byteOfValue[i];
			}
			return hashValue;
		}
	}
}