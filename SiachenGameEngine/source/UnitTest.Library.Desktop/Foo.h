#pragma once
// A helper class which contains a pointer to an integer which is dynamically allocated when an object is instantiated
// This class is made with the intention to perform unit testing using user defined types

namespace HelperClasses
{
	class Foo
	{
	public:
		// Default constructor allocates an integer of value 0
		Foo();
		// Allocates an integer of passed value
		Foo(int32_t);
		// Copy constructor
		Foo(const Foo&);
		// Destructor deallocates the assigned integer
		~Foo();
		// Assignment operator
		Foo& operator=(const Foo&);
		// Overloaded comparison operator
		bool operator==(const Foo&) const;
		// Get the integer value stored at m_pInteger
		int32_t GetValue() const;

	private:
		int32_t* m_pInteger;
	};
}