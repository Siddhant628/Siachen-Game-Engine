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
				/**
				* The hashmap to which the iterator is associated.
				*/
				HashMap* mOwnerMap;
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
				Iterator(HashMap* ownerMap, std::uint32_t bucketIndex, typename SList<PairType>::Iterator listIterator);
			
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
				* @return Value in the key-value pair in the hashmap referred to by the iterator.
				*/
				TData& operator*();
				/**
				* Dereference the key-value pair the iterator is associated with.
				* @return Key-value pair in the hashmap referred to by the iterator.
				*/
				const TData& operator*() const;
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
			* Returns an iterator which points to the beginning of this hashmap.
			* @return Iterator associated with the beginning of the hashmap.
			*/
			typename HashMap::Iterator begin() const;
			/**
			* Returns an iterator which points to beyond the last location in the hashmap
			* @return Iterator associated with the end of this hashmap.
			*/
			typename HashMap::Iterator end() const;

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