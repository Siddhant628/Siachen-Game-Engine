#pragma once
#include "RTTI.h"

// TODO Integrate GLM
#define GLM_FORCE_CXX11
#include "../../external/glm/glm/glm.hpp"


namespace SiachenGameEngine
{
	namespace Containers
	{
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
			Datum();

			Datum(const Datum& rhs);

			~Datum();

			// TODO 4 cases - Both sides could be internal or external
			Datum& operator=(const Datum& rhs);

			// Assignment operator overloads

			Datum& operator=(const std::int32_t rhs);
			Datum& operator=(const float rhs);
			Datum& operator=(const std::string& rhs);
			Datum& operator=(const glm::vec4& rhs);
			Datum& operator=(const glm::mat4x4& rhs);
			Datum& operator=(const GameplayFramework::RTTI* rhs);

			DatumType Type() const;

			bool SetType(DatumType setType);

			std::uint32_t Size() const;

			void PushBack(const std::int32_t data);
			void PushBack(const float data);
			void PushBack(const std::string& data);
			void PushBack(const glm::vec4& data);
			void PushBack(const glm::mat4x4& data);
			void PushBack(const GameplayFramework::RTTI* data);


			void Clear();

			void SetStorage(std::int32_t* externalArray, std::uint32_t numberOfElements);
			void SetStorage(float* externalArray, std::uint32_t numberOfElements);


		};
	}
}