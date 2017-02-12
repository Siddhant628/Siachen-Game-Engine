#pragma once
#include "RTTI.h"

// TODO Integrate GLM
#define GLM_FORCE_CXX11
#include "../../external/glm/glm/glm.hpp"


namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* An enum representing all the possible values that the Datum could possibly take at runtime.
		*/
		enum class DatumType
		{
			UnknownType,
			IntegerType,
			FloatType,
			VectorType,
			MatrixType,
			TableType,
			StringType,
			PointerType
		};

		class Datum
		{

		private:
			/**
			* A union of pointers to the types that a datum could possibly contain.
			*/
			union DatumValues
			{
				std::int32_t* i;
				std::float_t* f;
				glm::vec4* v;
				glm::mat4x4* m;
				std::string* s;
				GameplayFramework::RTTI** r;
				void* vp;
			};
			/**
			* The memory location where the data of the Datum is present.
			*/
			DatumValues mData;
			/**
			* The number of items inside the datum.
			*/
			std::uint32_t mSize;
			/**
			* The number of items that could fit inside the datum for the already allocated memory.
			*/
			std::uint32_t mCapacity;
			/**
			* The type of data stored in the Datum.
			*/
			DatumType mDatumType;
			/**
			* If the memory containing the data isn't owned by the Datum.
			*/
			bool mIsExternal;

		public:
			/**
			* Default Constructor - Initializes an empty Datum without any type or items in it.
			*/
			Datum();
			/**
			* Copy constructor - Performs a deep copy of the contents of rhs into this Datum.
			* @param rhs The datum whose contents have to be copied.
			*/
			Datum(const Datum& rhs);
			/**
			* Ensures that there are no memory leaks.
			*/
			~Datum();
			/**
			* Get the type of data which this datum stores.
			* @return The type for datum.
			*/
			DatumType Type() const;
			/**
			* Set the type of data which this datum stores.
			* @param setType The datum type which has to be set for this datum.
			*/
			void SetType(DatumType setType);
			/**
			* Get the size of the datum, i.e. the number of items in it.
			* @return The size as an unsigned integer.
			*/
			std::uint32_t Size() const;
			/**
			* Check whether a datum is empty.
			* @return True if the datum is empty.
			*/
			bool IsEmpty();
			/**
			* Reserve a specific amount of memory for the datum and move its data to it.
			* @param newCapacity The amount of capacity for which the memory has to be reserved.
			*/
			void Reserve(std::uint32_t newCapacity);
			/**
			* Push the item at the end of the datum.
			* @param data The integer to be pushed into the datum.
			*/
			void PushBack(const std::int32_t data);
			/**
			* Push the item at the end of the datum.
			* @param data The floating point number to be pushed into the datum.
			*/
			void PushBack(const std::float_t data);
			/**
			* Push the item at the end of the datum.
			* @param data The string to be pushed into the datum.
			*/
			void PushBack(const std::string& data);
			/**
			* Push the item at the end of the datum.
			* @param data The math vector to be pushed into the datum.
			*/
			void PushBack(const glm::vec4& data);
			/**
			* Push the item at the end of the datum.
			* @param data The matrix to be pushed into the datum.
			*/
			void PushBack(const glm::mat4x4& data);
			// TODO Scope PushBack

			/**
			* Push the item at the end of the datum.
			* @param data The RTTI* to be pushed into the datum.
			*/
			void PushBack(const GameplayFramework::RTTI* data);
			/**
			* Pop out the last item of the datum.
			*/
			void PopBack();
			/**
			* Clears the memory associated with the datum. However the memory remains reserved, i.e. the capacity remains unchanged.
			*/
			void Clear();
			/**
			* Clears and frees the memory used by the datum. This would reset the size and capacity to 0.
			*/
			void ClearAndFree();
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The item T stored in the datum.
			*/
			template<typename T>
			T& Get(std::uint32_t index = 0) const;
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The integer stored in the datum.
			*/
			template<>
			std::int32_t& Get(std::uint32_t index) const;
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The floating point number stored in the datum.
			*/
			template<>
			std::float_t& Get(std::uint32_t index) const;
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The vector stored in the datum.
			*/
			template<>
			glm::vec4& Get(std::uint32_t index) const;
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The matrix stored in the datum.
			*/
			template<>
			glm::mat4x4& Get(std::uint32_t index) const;
			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The string stored in the datum.
			*/
			template<>
			std::string& Get(std::uint32_t index) const;
			// TODO Scope Get specialization

			/**
			* Get a specific item stored in the datum.
			* @param index The position of the item to retrieve from the datum.
			* @return The RTTI* stored in the datum.
			*/
			template<>
			GameplayFramework::RTTI*& Get(std::uint32_t index) const;
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(std::int32_t value, std::uint32_t index = 0);
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(std::float_t value, std::uint32_t index = 0);
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(glm::vec4& value, std::uint32_t index = 0);
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(glm::mat4x4& value, std::uint32_t index = 0);
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(std::string& value, std::uint32_t index = 0);
			/**
			* Set the value of an item in the datum.
			* @param value The value that should be taken by the specific item in the datum.
			* @param index The index at which the value should be set.
			*/
			void Set(GameplayFramework::RTTI* value, std::uint32_t index = 0);
			// TODO Scope Set

			/**
			* Equals operator overloaded to compare two datums.
			* @param rhs The datum with which this datum should be compared.
			* @return True if the two datums are equal.
			*/
			bool operator==(const Datum& rhs) const;
			/**
			* Inequals operator overloaded to compare two datums.
			* @param rhs The datum with which this datum should be compared.
			* @return True if the two datums aren't equal.
			*/
			bool operator!=(const Datum& rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to an integer.
			* @param rhs The integer with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const std::int32_t rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to a float.
			* @param rhs The float with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const std::float_t rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to a string.
			* @param rhs The string with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const std::string& rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to an vector.
			* @param rhs The vector with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const glm::vec4& rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to a matrix.
			* @param rhs The matrix with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const glm::mat4x4& rhs) const;
			/**
			* Equals operator overloaded to compare a scalar datum to an RTTI*.
			* @param rhs The RTTI* with which this datum should be compared.
			* @return True if the two are equal.
			*/
			bool operator==(const GameplayFramework::RTTI* rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to an integer.
			* @param rhs The integer with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const std::int32_t rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to a float.
			* @param rhs The float with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const std::float_t rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to a string.
			* @param rhs The string with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const std::string& rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to a vector.
			* @param rhs The vector with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const glm::vec4& rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to a matrix.
			* @param rhs The matrix with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const glm::mat4x4& rhs) const;
			/**
			* Inequals operator overloaded to compare a scalar datum to a RTTI*.
			* @param rhs The RTTI* with which this datum should be compared.
			* @return True if the two aren't equal.
			*/
			bool operator!=(const GameplayFramework::RTTI* rhs) const;
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(std::int32_t* externalArray, std::uint32_t numberOfElements);
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(std::float_t* externalArray, std::uint32_t numberOfElements);
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(std::string* externalArray, std::uint32_t numberOfElements);
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(glm::vec4* externalArray, std::uint32_t numberOfElements);
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(glm::mat4x4* externalArray, std::uint32_t numberOfElements);
			/**
			* Associate datum with an external array.
			* @param externalArray A pointer to the memory location where the external array starts.
			* @param numberOfElements The number of items in the external array.
			*/
			void SetStorage(GameplayFramework::RTTI** externalArray, std::uint32_t numberOfElements);


			// TODO 4 cases - Both sides could be internal or external
			//Datum& operator=(const Datum& rhs);

			// Assignment operator overloads

			//Datum& operator=(const std::int32_t rhs);
			//Datum& operator=(const float rhs);
			//Datum& operator=(const std::string& rhs);
			//Datum& operator=(const glm::vec4& rhs);
			//Datum& operator=(const glm::mat4x4& rhs);
			//Datum& operator=(const GameplayFramework::RTTI* rhs);

		};
	}
}

#include "Datum.inl"