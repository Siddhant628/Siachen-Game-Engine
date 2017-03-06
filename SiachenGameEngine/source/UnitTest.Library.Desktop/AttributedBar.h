#pragma once
#include "AttributedFoo.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		/**
		* An attributed class which derives from AttributedFoo.
		*/
		class AttributedBar final : public AttributedFoo
		{
			RTTI_DECLARATIONS(AttributedBar, AttributedFoo)

		private:
			std::float_t mFloat;
			std::string mString;
			glm::vec4 mVec4;
			glm::mat4x4 mMat4x4;
			GameplayFramework::RTTI* mRTTI;

		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedBar();
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			~AttributedBar();
			/**
			* Populate the AttributedBar with prescribed attributes of this class.
			*/
			void Populate() override;

			std::float_t GetFloat() const;

			const std::string GetString() const;

			glm::vec4 GetVector() const;

			glm::mat4x4 GetMatrix() const;

			std::int32_t GetRTTIFoo() const;

			void SetFloat(std::float_t value);

			void SetString(const std::string& str);

			void SetVector(glm::vec4& vector);

			void SetMatrix(glm::mat4x4& matrix);

			void SetRTTIFoo(std::int32_t value);

		};
	}
}