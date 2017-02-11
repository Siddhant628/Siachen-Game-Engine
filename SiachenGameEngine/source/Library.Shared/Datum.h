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
				float* f;
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
			// TODO Implement PushBack for Scope type.

			/**
			* Push the item at the end of the datum.
			* @param data The RTTI* to be pushed into the datum.
			*/
			void PushBack(const GameplayFramework::RTTI* data);

			// TODO Would we need to call destructor?
			void PopBack();

			void Clear();

			void ClearAndFree();

			// TODO 4 cases - Both sides could be internal or external
			//Datum& operator=(const Datum& rhs);

			// Assignment operator overloads

			//Datum& operator=(const std::int32_t rhs);
			//Datum& operator=(const float rhs);
			//Datum& operator=(const std::string& rhs);
			//Datum& operator=(const glm::vec4& rhs);
			//Datum& operator=(const glm::mat4x4& rhs);
			//Datum& operator=(const GameplayFramework::RTTI* rhs);


			//void Clear();

			//void SetStorage(std::int32_t* externalArray, std::uint32_t numberOfElements);
			//void SetStorage(float* externalArray, std::uint32_t numberOfElements);


		};
	}
}