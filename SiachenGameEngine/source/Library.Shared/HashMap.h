#pragma once
#include <cstdint>
#include <utility>
#include <string>
#include "Vector.h"
#include "SList.h"
#include "Foo.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* A HashMap container which uses a vector of singly linked lists (for chaining) to store data.
		*/
		template<typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
		class HashMap final
		{

		private:
			typedef std::pair<TKey, TData> PairType;
			typedef SList<PairType> ChainType;
			typedef Vector<ChainType> BucketType;
			/**
			* The vector containing all the data of the hash map.
			*/
			BucketType mHashmap;
			uint32_t mSize;
		public:
			/**
			* An Iterator class for the HashMap container.
			*/
			class Iterator
			{
				friend class HashMap;
			private:
				/**
				* The hashmap to which the iterator is associated.
				*/
				const HashMap* mOwnerMap;
				/**
				* The bucket index to which the iterator is associated with, in this case, the specific SList in the Vector.
				*/
				std::uint32_t mBucketIndex;
				/**
				* An iterator associated with a specific node in the SList where the key-value pair is stored.
				*/
				typename SList<PairType>::Iterator mListIterator;

				/**
				* A private constructor which initializes the iterator with passes arguments
				* @param ownerMap A pointer to the hash map with which the iterator is associated.
				* @param bucketIndex The index of the bucket in the hash map where the key-value pair's SList is stored.
				* @param listIterator The iterator associated with a specific node in the SList.
				*/
				Iterator(const HashMap* ownerMap,const std::uint32_t bucketIndex, const typename SList<PairType>::Iterator listIterator);
			
			public:
				/**
				* A default constructor which initializes the Iterator.
				*/
				Iterator();
				/**
				* A copy constructor which performs a deep copy of the passed iterator object into this object.
				* @param it An iterator object which has to be copied into this object.
				*/
				Iterator(const Iterator &it);
				/**
				* Assignment operator overloaded to perform a deep copy of an iterator into this iterator.
				* @param it The iterator which has to be copied.
				* @return A deep copy of iterator it.
				*/
				Iterator& operator=(const Iterator &it);
				/**
				* Compares if two iterators are associated with the same key-value pair.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators are associated with the same key-value pair.
				*/
				bool operator==(const Iterator &it) const;
				/**
				* Compares if two iterators aren't associated with the same key-value pair.
				* @param it The iterator to compare this iterator with.
				* @return True if two iterators aren't associated with the same key-value pair.
				*/
				bool operator!=(const Iterator &it) const;
				/**
				* Overloaded pre-increment operator increments to the next key-value pair in the hashmap.
				* @return Iterator associated with to the next key-value pair.
				*/
				Iterator& operator++();
				/**
				* Overloaded post-increment operator increments the item to which it is associated with in the hashmap.
				* @return Iterator associated with to the same key-value pair.
				*/
				Iterator operator++(std::int32_t);
				/**
				* Dereference the key-value pair the iterator is associated with.
				* @return Key-value pair in the hashmap referred to by the iterator.
				*/
				PairType& operator*();
				/**
				* Dereference the key-value pair the iterator is associated with.
				* @return Key-value pair in the hashmap referred to by the iterator.
				*/
				const PairType& operator*() const;
				/**
				* Dereference the key-value pair the iterator is associated with.
				* @return Key-value pair in the hashmap referred to by the iterator.
				*/
				PairType& operator->();
				/**
				* Dereference the key-value pair the iterator is associated with.
				* @return Key-value pair in the hashmap referred to by the iterator.
				*/
				const PairType& operator->() const;
			};
			/**
			* Constructor which makes an initialized vector of specified size to store value-type pairs.
			* @param numberOfBuckets The number of buckets the initialized hash map will have (default value is 13)
			*/
			explicit HashMap(std::uint32_t numberOfBuckets = 13);

			/**
			* Returns an iterator which points to first key-value pair in the hashmap
			* @return Iterator associated with the first key-value pair of the hashmap.
			*/
			typename HashMap::Iterator begin() const;
			/**
			* Returns an iterator which points to beyond the last SList in the hashmap
			* @return Iterator associated with the end of this hashmap.
			*/
			typename HashMap::Iterator end() const;
			/**
			* Look for a specific key in the hashmap.
			* @param key The key which has to be searched for in the hashmap.
			* @return An iterator to the found key in the hash map, if not found it returns an iterator to the end.
			*/
			typename HashMap::Iterator Find(const TKey& key) const;
			/**
			* Insert a specific key-value pair into the hashmap.
			* @param pair The key-value pair which has to be inserted.
			* @return An iterator associated with the inserted key-value pair
			*/
			typename HashMap::Iterator Insert(const PairType& pair);
			/**
			* Remove the specified key from the hashmap.
			* @param key The key whose associated value pair needs to be removed from the hashmap.
			* @return True if a key-value pair is successfully removed.
			*/
			bool Remove(const TKey &key);
			/**
			* Empty the hashmap and delete the memory allocated to it.
			*/
			void Clear();
			/**
			* Get the population of the table.
			* @return The number of key-value pairs inside the hashmap.
			*/
			std::uint32_t Size() const;
			/**
			* Check if a key is present in the hashmap.
			* @param key The key to check for presence.
			* @return True if the key is present in the hashmap.
			*/
			bool ContainsKey(const TKey& key) const;

			/**
			* Overloaded subscript operator returns the value associated with the input key, if input key isn't found, it inserts it.
			* @param key The key value whose associated data is output.
			* @return The data in the hashmap associated with the input key.
			*/
			TData& operator[](const TKey &key);
			/**
			* Overloaded subscript operator returns the value associated with the input key.
			* @param key The key value whose associated data is output.
			* @return The data in the hashmap associated with the input key.
			*/
			const TData& operator[](const TKey &key) const;

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
			std::uint32_t operator()(char* key) const;
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
		/**
		* Default has functor's specialization for Foo class.
		*/
		template<>
		class DefaultHash <HelperClasses::Foo>
		{
		public:
			std::uint32_t operator()(const HelperClasses::Foo &foo) const;
		};
	}
}

#include "HashMap.inl"