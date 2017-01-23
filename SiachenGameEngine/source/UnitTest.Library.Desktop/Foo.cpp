#include "pch.h"
#include "Foo.h"
namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		Foo::Foo() : m_pInteger(new int32_t(0))
		{

		}

		Foo::Foo(int32_t value)
		{
			m_pInteger = new int32_t(value);
		}

		Foo::Foo(const Foo& obj)
		{
			m_pInteger = new int32_t(*(obj.m_pInteger));
		}

		Foo::~Foo()
		{
			delete m_pInteger;
		}

		Foo& Foo::operator=(const Foo& rhs)
		{
			*m_pInteger = *(rhs.m_pInteger);
			return *this;
		}

		bool Foo::operator==(const Foo& rhs) const
		{
			return (*m_pInteger == *(rhs.m_pInteger));
		}

		int32_t Foo::GetValue() const
		{
			return *m_pInteger;
		}
	}
}