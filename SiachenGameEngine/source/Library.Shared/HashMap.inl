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

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, doesn't belong to any Hashmap.");
			}
			if (*this == mOwnerMap->end())
			{
				throw std::runtime_error("Iterator cannot pre-increment, end has been reached.\n");
			}

			std::uint32_t indexInVector = mBucketIndex;
			SList<PairType>::Iterator it == mListIterator;
			bool exceptionThrown = false;

			// Handle the case for the key-value pairs within the same SList as the iterator.
			try
			{
				for (++it; it != mOwnerMap->mHashmap[indexInVector].end(); ++it)
				{
					try
					{
						*it;
					}
					catch (const std::exception&)
					{
						exceptionThrown = true;
					}
					if (!exceptionThrown)
					{
						mBucketIndex = indexInVector;
						mListIterator = it;
						return *this;
					}
					exceptionThrown = false;
				}
				++indexInVector;
			}
			// Move to the next index of vector in case this node was the last SList node.
			catch (const std::exception&)
			{
				++indexInVector;
			}
			// Iterate over the remaining Vector to get the next valid key-value pair.
			while (indexInVector < mOwnerMap->mHashmap.Size())
			{
				for (it = mOwnerMap->mHashmap[indexInVector].begin(); it != mOwnerMap->mHashmap[indexInVector].end(); ++it)
				{
					try
					{
						*it;
					}
					catch (const std::exception&)
					{
						exceptionThrown = true;
					}
					if (!exceptionThrown)
					{
						mBucketIndex = indexInVector;
						mListIterator = it;
						return *this;
					}
					exceptionThrown = false;
				}
				++indexInVector;
			}
			return mOwnerMap->end();
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(std::int32_t)
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Iterator cannot pre-increment, doesn't belong to any Hashmap.");
			}
			if (*this == mOwnerMap->end())
			{
				throw std::runtime_error("Iterator cannot pre-increment, end has been reached.\n");
			}

			std::uint32_t indexInVector = mBucketIndex;
			SList<PairType>::Iterator it == mListIterator;
			bool exceptionThrown = false;
			Iterator tempIt = *this;

			// Handle the case for the key-value pairs within the same SList as the iterator.
			try
			{
				for (++it; it != mOwnerMap->mHashmap[indexInVector].end(); ++it)
				{
					try
					{
						*it;
					}
					catch (const std::exception&)
					{
						exceptionThrown = true;
					}
					if (!exceptionThrown)
					{
						mBucketIndex = indexInVector;
						mListIterator = it;
						return tempIt;
					}
					exceptionThrown = false;
				}
				++indexInVector;
			}
			// Move to the next index of vector in case this node was the last SList node.
			catch (const std::exception&)
			{
				++indexInVector;
			}
			// Iterate over the remaining Vector to get the next valid key-value pair.
			while (indexInVector < mOwnerMap->mHashmap.Size())
			{
				for (it = mOwnerMap->mHashmap[indexInVector].begin(); it != mOwnerMap->mHashmap[indexInVector].end(); ++it)
				{
					try
					{
						*it;
					}
					catch (const std::exception&)
					{
						exceptionThrown = true;
					}
					if (!exceptionThrown)
					{
						mBucketIndex = indexInVector;
						mListIterator = it;
						return tempIt;
					}
					exceptionThrown = false;
				}
				++indexInVector;
			}
			*this = mOwnerMap->end();
			return tempIt;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename TData& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator).second;

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename const TData& HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator).second;

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
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

		// HashMap methods

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin() const
		{
			std::uint32_t indexInVector = 0;
			SList<PairType>::Iterator it;
			bool exceptionThrown = false;

			while (indexInVector < mHashmap.Size())
			{
				for (it = mHashmap[indexInVector].begin(); it != mHashmap[indexInVector].end(); ++it)
				{
					try
					{
						*it;
					}
					catch (const std::exception&)
					{
						exceptionThrown = true;
					}
					if (!exceptionThrown)
					{
						return Iterator(this, indexInVector, it);
					}
					exceptionThrown = false;
				}
				++indexInVector;
			}
			return end();
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end() const
		{
			return Iterator(this, mHashmap.Size()-1, mHashmap[mHashmap.Size() - 1].end());
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