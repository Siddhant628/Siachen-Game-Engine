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

		// Iterator operations

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

			std::uint32_t indexInVector = mBucketIndex;
			SList<PairType>::Iterator it = mListIterator;
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
			*this = mOwnerMap->end();
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
		typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->mHashmap.Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator);

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename const HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->mHashmap.Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator);

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator->()
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->mHashmap.Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator);

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename const HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
		{
			if (mOwnerMap == nullptr)
			{
				throw std::runtime_error("Cannot dereference an iterator which isn't associated with a hashmap.");
			}
			if (mBucketIndex >= mOwnerMap->mHashmap.Size())
			{
				throw std::out_of_range("Cannot dereference an items outside the hashmap.");
			}
			try
			{
				return (*mListIterator);

			}
			catch (const std::exception&)
			{
				throw std::runtime_error("Failed at dereferencing the key-value pair.");
			}
		}

		// HashMap constructors

		template<typename TKey, typename TData, typename HashFunctor>
		HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t numberOfBuckets) : mHashmap(BucketType(numberOfBuckets)), mSize(0)
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
			SList<PairType>::Iterator it = (mHashmap[mHashmap.Size() - 1]).end();
			return Iterator(this, (mHashmap.Size()-1), it);
		}

		template<typename TKey, typename TData, typename HashFunctor>
		typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey &key) const
		{
			HashFunctor hash;
			uint32_t index = (hash(key) % mHashmap.Size());
			
			for (SList<PairType>::Iterator it = mHashmap[index].begin(); it != mHashmap[index].end(); ++it)
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
			uint32_t index = (hash(key) % mHashmap.Size());
			SList<PairType>::Iterator listIterator = mHashmap[index].PushBack(pair);
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
				mHashmap[it.mBucketIndex].Remove(*it);
				--mSize;
				return true;
			}
		}

		// TODO Check for memory leaks
		template<typename TKey, typename TData, typename HashFunctor>
		void HashMap<TKey, TData, HashFunctor>::Clear()
		{
			mHashmap.ClearAndFree();
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
		TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey &key)
		{
			HashMap::Iterator it = Find(key);
			if (it == end())
			{
				std::pair<TKey, TData> pair(key, TData());
				++mSize;
				Insert(pair);
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