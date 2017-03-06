#pragma once
#include "Attributed.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		/**
		* An attributed class which derives directly from Attributed.
		*/
		class AttributedFoo : public GameplayFramework::Attributed
		{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)

		private:
			/**
			* An integer value.
			*/
			std::int32_t mInteger;
		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedFoo();
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			virtual ~AttributedFoo() = default;
			/**
			* Populate the AttributedFoo with prescribed attributes of this class.
			*/
			void Populate() override;
			/**
			* Get the value of mInteger.
			* @return The value of mInteger.
			*/
			std::int32_t GetInteger() const;
			/**
			* Set the value of mInteger.
			* @param value The value to set for mInteger.
			*/
			void SetInteger(std::int32_t value);

		};
	}
}