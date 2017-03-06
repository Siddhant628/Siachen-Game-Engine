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
			/**
			* A float value.
			*/
			std::float_t mFloat;

		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedBar();
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			~AttributedBar() = default;
			/**
			* Populate the AttributedBar with prescribed attributes of this class.
			*/
			void Populate() override;
			/**
			* Get the value of mFloat.
			* @return The value of mFloat.
			*/
			std::float_t GetFloat();
			/**
			* Set the value of mFloat.
			* @param value The value to set for mFloat.
			*/
			void SetFloat(std::float_t value);

		};
	}
}