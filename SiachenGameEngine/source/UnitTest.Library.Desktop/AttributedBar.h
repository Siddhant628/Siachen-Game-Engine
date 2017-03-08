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

			void DeepCopyAttributedBar(const AttributedBar& rhs);
		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedBar();
			/*
			* Copy constructor - Performs a deep copy of rhs into this attributed bar.
			* @param rhs The attributed bar which has to be copied into this.
			*/
			AttributedBar(const AttributedBar& rhs);
			/*
			* Assignment Operator - Performs a deep copy of rhs into this attributed bar.
			* @param rhs The attributed bar which has to be deep copied into this attributed bar.
			* @return A reference to a attributed bar with a deep copy of rhs.
			*/
			AttributedBar& operator=(const AttributedBar& rhs);
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			virtual ~AttributedBar();
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