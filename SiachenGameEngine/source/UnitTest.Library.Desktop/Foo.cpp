#include "pch.h"
#include "Foo.h"
namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		Foo::Foo() : mIntegerPointer(new int32_t(0))
		{

		}

		Foo::Foo(int32_t value)
		{
			mIntegerPointer = new int32_t(value);
		}

		Foo::Foo(const Foo& obj)
		{
			mIntegerPointer = new int32_t(*(obj.mIntegerPointer));
		}

		Foo::~Foo()
		{
			delete mIntegerPointer;
		}

		Foo& Foo::operator=(const Foo& rhs)
		{
			*mIntegerPointer = *(rhs.mIntegerPointer);
			return *this;
		}

		bool Foo::operator==(const Foo& rhs) const
		{
			return (*mIntegerPointer == *(rhs.mIntegerPointer));
		}

		int32_t Foo::GetValue() const
		{
			return *mIntegerPointer;
		}
	}
}