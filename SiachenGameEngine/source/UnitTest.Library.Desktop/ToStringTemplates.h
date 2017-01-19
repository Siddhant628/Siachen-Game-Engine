#pragma once

// To String implementation for helper class Foo.
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{

			template<>
			std::wstring ToString<HelperClasses::Foo>(const HelperClasses::Foo  & foo)
			{
				int32_t value = foo.GetValue();
				std::string str = std::to_string(value);
				std::wstring wideStr = std::wstring(str.begin(), str.end());
				return wideStr.c_str();
			}

		}
	}
}