#pragma once

namespace HelperClasses
{
	class Foo
	{
	public:
		Foo();
		Foo(int32_t);
		Foo(const Foo&);
		~Foo();
		Foo& operator=(const Foo&);
		bool operator==(const Foo&) const;

		int32_t GetValue() const;
		
	private:
		int32_t* m_pInteger;
	};
}