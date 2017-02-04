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
		HashMap<TKey, TData, HashFunctor>::Iterator::Iterator( const HashMap* ownerMap, const std::uint32_t bucketIndex, const typename SList<PairType>::Iterator listIterator) : mOwnerMap(ownerMap), mBucketIndex(bucketIndex), mListIterator(listIterator)
		{

		}

		// Iterator operators

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator &it)
		{
			if(this != &it)
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

			HashMap<TKey, TData, HashFunctor>::Iterator iteratorToReturn = mOwnerMap->end();
			std::uint32_t indexInVector = mBucketIndex;
			SList<PairType>::Iterator it = mListIterator;
			
			// Handle the case for the key-value pairs within the same SList as the iterator
			try
			{
				++it;
				for (; it != mOwnerMap->mHashmapVector[indexInVector].end(); ++it)
				{
					mBucketIndex = indexInVector;
					mListIterator = it;
					iteratorToReturn = *this;
					// If iterator to return is found, break
					if (iteratorToReturn != mOwnerMap->end())
					{
						break;
					}
				}
				++indexInVector;
			}
			// Move to the next index of vector in case this node was the last SList node
			catch (const std::exception&)
			{
				++indexInVector;
			}
			// Iterate over the remaining Vector to get the next valid key-value pair
			while (indexInVector < mOwnerMap->mHashmapVector.Size())
			{
				for (it = mOwnerMap->mHashmapVector[indexInVector].begin(); it != mOwnerMap->mHashmapVector[indexInVector].end(); ++it)
				{
					mBucketIndex = indexInVector;
					mListIterator = it;
					iteratorToReturn = *this;
					// If iterator to return is found, break
					if (iteratorToReturn != mOwnerMap->end())
					{
						break;
					}
				}
				++indexInVector;
				// If iterator to return is found, break
				if (iteratorToReturn != mOwnerMap->end())
				{
					break;
				}
			}
			*this = iteratorToReturn;
			return *this;
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
			SList<PairType>::Iterator it = mListIterator;

			Iterator iteratorBeforeOperation = *this;
			Iterator iteratorAfterOperation = *this;

			// Handle the case for the key-value pairs within the same SList as the iterator
			try
			{
				for (++it; it != mOwnerMap->mHashmapVector[indexInVector].end(); ++it)
				{
						mBucketIndex = indexInVector;
						mListIterator = it;
						iteratorAfterOperation = *this;
						// If incremented to the next key-value pair, break
						if (iteratorAfterOperation != iteratorBeforeOperation)
						{
							break;
						}
				}
				++indexInVector;
			}
			// Move to the next index of vector in case this node was the last SList node
			catch (const std::exception&)
			{
				++indexInVector;
			}
			// Iterate over the remaining Vector to get the next valid key-value pair
			while (indexInVector < mOwnerMap->mHashmapVector.Size())
			{
				for (it = mOwnerMap->mHashmapVector[indexInVector].begin(); it != mOwnerMap->mHashmapVector[indexInVector].end(); ++it)
				{
						mBucketIndex = indexInVector;
						mListIterator = it;
						iteratorAfterOperation = *this;
						// If incremented to the next key-value pair, break
						if (iteratorAfterOperation != iteratorBeforeOperation)
						{
							break;
						}
				}
				++indexInVector;
				// If incremented to the next key-value pair, break
				if (iteratorAfterOperation != iteratorBeforeOperation)
				{
					break;
				}
			}
			// If couldn't find any key-value pair, increment to end of the map
			if(iteratorAfterOperation == iteratorBeforeOperation)
			{ 
				*this = mOwnerMap->end();
			}
			return iteratorBeforeOperation;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			return (*mListIterator);
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename const HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			return (*mListIterator);
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator->()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			return (*mListIterator);
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename const HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			return (*mListIterator);
		}

		// HashMap constructors

		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t numberOfBuckets) : mHashmapVector(BucketType(numberOfBuckets)), mSize(0)
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
			HashMap<TKey, TData, HashFunctor>::Iterator hashmapIt = end();

			while (indexInVector < mHashmapVector.Size())
			{
				for (it = mHashmapVector[indexInVector].begin(); it != mHashmapVector[indexInVector].end(); ++it)
				{
						hashmapIt = Iterator(this, indexInVector, it);
						if (hashmapIt != end())
						{
							break;
						}
				}
				if (hashmapIt != end())
				{
					break;
				}
				++indexInVector;
			}
			return hashmapIt;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end() const
		{
			SList<PairType>::Iterator it;
			if (mHashmapVector.Size() == 0)
			{
				it = mHashmapVector[0].end();
				return Iterator(this, 0, it);
			}
			else
			{
				it = mHashmapVector[mHashmapVector.Size() - 1].end();
				return Iterator(this, (mHashmapVector.Size() - 1), it);
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey &key) const
		{
			if (mSize == 0)
			{
				return end();
			}
			HashFunctor hash;
			uint32_t index = (hash(key) % mHashmapVector.Size());
			
			for (SList<PairType>::Iterator it = mHashmapVector[index].begin(); it != mHashmapVector[index].end(); ++it)
			{
				if ((*it).first == key)
				{
					return Iterator(this, index, it);
				}
			}
			return end();
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType &pair)
		{
			TKey key = pair.first;
			// In case the key is already present in the map
			HashMap::Iterator it = Find(key);
			if (it != end())
			{
				return it;
			}
			// In case the key isn't present in the map
			HashFunctor hash;
			uint32_t index = (hash(key) % mHashmapVector.Size());
			SList<PairType>::Iterator listIterator = mHashmapVector[index].PushBack(pair);
			++mSize;
			return Iterator(this, index, listIterator);
		}

		template<typename TKey, typename TData, typename HashFunctor>
		bool HashMap<TKey, TData, HashFunctor>::Remove(const TKey &key)
		{
			HashMap::Iterator it = Find(key);
			if (it == end())
			{
				return false;
			}
			else
			{
				mHashmapVector[it.mBucketIndex].Remove(*it);
				--mSize;
				return true;
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		void HashMap<TKey, TData, HashFunctor>::Clear()
		{
			std::int32_t sizeOfVector = mHashmapVector.Size();
			for (std::int32_t index = 0; index < sizeOfVector; ++index)
			{
				mHashmapVector[index].Clear();
			}
			mSize = 0;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		std::uint32_t HashMap<TKey, TData, HashFunctor>::Size() const
		{
			return mSize;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey & key) const
		{
			HashMap::Iterator it = Find(key);
			if (it == end())
			{
				return false;
			}
			return true;
		}

		// HashMap operators

		template<typename TKey, typename TData, typename HashFunctor>
		TData HashMap<TKey, TData, HashFunctor>::operator[](const TKey &key)
		{
			std::pair<TKey, TData> pair(key, TData());
			HashMap::Iterator it = Find(key);
			if (it == end())
			{
				Insert(pair);
			}
			else
			{
				pair = *it;
			}
			return pair.second;
		}

		template<typename TKey, typename TData, typename HashFunctor>
		const TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey &key) const
		{
			HashMap::Iterator it = Find(key);
			if (it == end())
			{
				throw std::runtime_error("No value stored in the map corresponding to the entered key.");
			}
			return (*it).second;
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

		std::uint32_t DefaultHash<char*>::operator()(char* key) const
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