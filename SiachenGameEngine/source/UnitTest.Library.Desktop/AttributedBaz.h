#pragma once

#include "Attributed.h"
#include "RTTI.h"
#include "Foo.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		/**
		* An attributed class which derives directly from Attributed.
		*/
		class AttributedBaz final : public GameplayFramework::Attributed
		{
			RTTI_DECLARATIONS(AttributedBaz, Attributed)

		private:
			/**
			* An integer value.
			*/
			std::int32_t mInteger;

			Foo* foo;
			Foo* foo2;
		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedBaz();
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			~AttributedBaz();
			/**
			* Populate the AttributedFoo with prescribed attributes of this class.
			*/
			void Populate() override;
		};
	}
}