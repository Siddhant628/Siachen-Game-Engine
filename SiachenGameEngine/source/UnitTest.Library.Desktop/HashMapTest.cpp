#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(First_Test)
		{
			HashMap<int, int>::Iterator it;
			HashMap<int, int> randomMap(10);
		}

		TEST_METHOD(Default_Hash_Functor)
		{
			// Default hash function
			DefaultHash<std::int32_t> intHash;
			std::uint32_t a = 1000, b = 1000;
			Assert::AreEqual(intHash(a), intHash(b));

			// Specialization for string keys
			DefaultHash<std::string> stringHash;
			std::string str = "Hey";
			std::string str2 = str;
			Assert::AreEqual(stringHash(str), stringHash(str2));

			// Specialization for char*
			DefaultHash<char*> charHash;
			const char* str3 = "Hey";
			const char* str4 = "yeH";
			Assert::AreEqual(charHash(str3), charHash(str4));

			// Specialization for Foo
			DefaultHash<Foo> fooHash;
			Foo foo(a), foo2(b);
			Assert::AreEqual(fooHash(foo), fooHash(foo2));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}