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
			/*
			* Preforms a deep copy of a attributed foo into this one.
			* @param rhs The attributed foo whose deep copy is to be performed.
			*/
			void DeepCopyAttributedFoo(const AttributedFoo& rhs);
		public:
			/**
			* Default Constructor - Populates the scope with prescribed attributes.
			*/
			AttributedFoo();
			/*
			* Copy constructor - Performs a deep copy of rhs into this attributed foo.
			* @param rhs The attributed foo which has to be copied into this.
			*/
			AttributedFoo(const AttributedFoo& rhs);
			/*
			* Assignment Operator - Performs a deep copy of rhs into this attributed foo.
			* @param rhs The attributed scope which has to be deep copied into this attributed foo.
			* @return A reference to a attributed foo with a deep copy of rhs.
			*/
			AttributedFoo& operator=(const AttributedFoo& rhs);
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