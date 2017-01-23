#pragma once

// To String implementation for helper class Foo.
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{

			template<>
			std::wstring ToString<SiachenGameEngine::HelperClasses::Foo>(const SiachenGameEngine::HelperClasses::Foo& foo)
			{
				std::wstringstream bufferStream;
				int32_t value = foo.GetValue();
				bufferStream << "Foo_SList_" << value;
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<SiachenGameEngine::Containers::SList<int32_t>::Iterator>(typename const SiachenGameEngine::Containers::SList<int32_t>::Iterator& It)
			{
				std::wstringstream bufferStream;
				try
				{
					int32_t value = *It;
					bufferStream << "Integer_Iterator_" << value;
				}
				catch (std::exception)
				{

				}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<SiachenGameEngine::Containers::SList<int32_t*>::Iterator>(typename const SiachenGameEngine::Containers::SList<int32_t*>::Iterator& It)
			{
				std::wstringstream bufferStream;
				try 
				{
					int32_t* value = *It;
					bufferStream << "Integer*_Iterator_" << value;
				}
				catch (std::exception)
				{

				}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<SiachenGameEngine::Containers::SList<SiachenGameEngine::HelperClasses::Foo>::Iterator>(typename const SiachenGameEngine::Containers::SList<SiachenGameEngine::HelperClasses::Foo>::Iterator& It)
			{
				std::wstringstream bufferStream;
				try 
				{
					int32_t value = (*It).GetValue();
					bufferStream << "Foo_Iterator_" << value;
				}
				catch(std::exception)
				{

				}
				return bufferStream.str();
			}

		}
	}
}