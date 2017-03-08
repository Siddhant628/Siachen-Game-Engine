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
			Scope* scope;
			
		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedBaz();
			/*
			* Copy constructor - Performs a deep copy of rhs into this attributed baz.
			* @param rhs The attributed baz which has to be copied into this.
			*/
			AttributedBaz(const AttributedBaz& rhs);
			/*
			* Assignment Operator - Performs a deep copy of rhs into this attributed baz.
			* @param rhs The attributed baz which has to be deep copied into this attributed baz.
			* @return A reference to a attributed baz with a deep copy of rhs.
			*/
			AttributedBaz& operator=(const AttributedBaz& rhs);

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