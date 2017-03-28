#pragma once
#include "RTTI.h"
#include "Factory.h"
// A helper class which contains a pointer to an integer which is dynamically allocated when an object is instantiated
// This class is made with the intention to perform unit testing using user defined types

namespace SiachenGameEngine
{
	namespace HelperClasses
	{

		class Foo : public GameplayFramework::RTTI
		{
			RTTI_DECLARATIONS(Foo, GameplayFramework::RTTI)
		public:
			// Default constructor allocates an integer of value 0
			Foo();
			// Allocates an integer of passed value
			Foo(int32_t);
			// Copy constructor
			Foo(const Foo&);
			// Destructor deallocates the assigned integer
			virtual ~Foo();
			// Assignment operator
			Foo& operator=(const Foo&);
			// Overloaded comparison operator
			bool operator==(const Foo&) const;
			// Get the integer value stored at mIntegerPointer
			int32_t GetValue() const;

			void SetValue(std::int32_t value);

			virtual bool Equals(const RTTI* rhs) const override;

			virtual std::string ToString() const override;

		private:
			int32_t* mIntegerPointer;
		};

		ConcreteFactory(GameplayFramework::RTTI, Foo);
	}
}